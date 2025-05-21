#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#include "buffer.h" 

buffer_item buffer[BUFFER_SIZE];
int buffer_count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex;
sem_t empty, full;

void *producer(void *param);
void *consumer(void *param);
void initialize_buffer();
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sleep_time> <num_producers> <num_consumers>\n", argv[0]);
        return 1;
    }
    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);
    initialize_buffer();

    pthread_t producer_threads[num_producers];
    pthread_t consumer_threads[num_consumers];
    for (int i = 0; i < num_producers; i++)
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    for (int i = 0; i <num_consumers; i++)
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
 
    sleep(sleep_time);
    return 0;
}

void initialize_buffer() {
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
}

void *producer(void *param) {
    buffer_item item;
    while (1) {
      
        usleep(rand() % 1000000); 
        item = rand()%100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        if (insert_item(item) == -1)
            printf("Error: Buffer is full\n");
        else
            printf("Producer produced %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *param) {

    buffer_item item;
    while (1) {
        usleep(rand() % 1000000); 
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        if (remove_item(&item) == -1)
            printf("Error: Buffer is empty\n");
        else
            printf("Consumer consumed %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

int insert_item(buffer_item item) {
    
    if (buffer_count == BUFFER_SIZE)
        return -1; // Buffer is full, cannot insert
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    buffer_count++;

    return 0; 
}

int remove_item(buffer_item *item) {

    if (buffer_count == 0)
        return -1; 
    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    buffer_count--;

    return 0; 
}

