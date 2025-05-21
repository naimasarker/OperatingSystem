#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

int count = 0;
double pi;

void *runner1(void *param);

int main(int argc, char *argv[]){
    pthread_t tid;
    pthread_attr_t attr;
    
    if(argc < 2){
       fprintf(stderr, "usage: %s\n", argv[0]);
       return -1;
    }
    
    if (atoi(argv[1]) > 101) {
	fprintf(stderr,"Argument %d must be less than 101\n",atoi(argv[1]));
	return -1;
    }
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner1, argv[1]);
    pthread_join(tid, NULL);
    
    printf("The value of pi is : %lf\n", pi);
    
}

void *runner1(void *param){
     srand(time(NULL));
     int i, upper = atoi(param);
     double random_numX;
     double random_numY;
     for (int i=0; i<upper; i++){
        random_numX = ((double)rand() / RAND_MAX) * 2 - 1;
        random_numY = ((double)rand() / RAND_MAX) * 2 - 1;
        if(abs(sqrt(pow(random_numX - 0, 2) + pow(random_numY - 0, 2) * 1.0)) < 1){
           count++;
        }
     }
     //printf("%d ", count);
     //printf("%d ", upper);
     pi = 4.0*(count) / upper; 
     pthread_exit(0);
}
