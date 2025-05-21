#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> 
#define Max_readers 5

int read_count = 0;

sem_t rw_mutex, mutex;

void *reader(void *arg);
void *writer(void *arg);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sleep_time>\n", argv[0]);
        return 1;
    }
    int sleep_time = atoi(argv[1]);
    FILE *file = fopen("example.txt", "a+");
    if(!file){
      perror("Error opening file.");
      return 1;
    }
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    pthread_t writer_thread, reader_thread;
    pthread_create(&reader_thread, NULL, reader, (void *)file);
    pthread_create(&writer_thread, NULL, writer, (void *)file);

    pthread_join(reader_thread, NULL);
    pthread_join(writer_thread, NULL);
    fclose(file);
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);
    sleep(sleep_time);
    return 0;
}

void *reader(void *arg) {
    FILE *file = (FILE *) arg;
    while (1) {
        usleep(rand() % 1000000); 
        sem_wait(&mutex);
        read_count++;
        if (read_count == 1)
           sem_wait(&rw_mutex);
        sem_post(&mutex);
        char buffer[256];
        fgets(buffer, sizeof(buffer), file);
        printf("Read: %s", buffer);
        sem_wait(&mutex);
        read_count--;
        if(read_count == 0)
           sem_post(&rw_mutex);
        sem_post(&mutex);
        
    }
    pthread_exit(NULL);
}
void *writer(void *arg) {
    FILE *file = (FILE *) arg;
    while (1) {
        usleep(rand() % 1000000); 
        sem_wait(&rw_mutex);
        printf("Writing time.\n");
        fprintf(file, "Hello Naima");
        fflush(file);
        sem_post(&rw_mutex);
        
    }
    pthread_exit(NULL);
}
