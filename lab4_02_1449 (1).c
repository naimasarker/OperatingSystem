#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void multi(int i, int A[3][3], int B[3][3]){
     int result[3];
    for (int j = 0; j <3; j++) {
        result[j] = 0;
        for (int k = 0; k < 3; k++) {
            result[j] += A[i][k] * B[k][j];
        }
    }
    printf("Result for row %d: ", i);
    for (int j = 0; j <3; j++) {
        printf("%d ", result[j]);
    }
    printf("\n");
    exit(0);
}

int main(){

    int A[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int B[3][3] = {{9, 8, 7}, {6, 5, 4},{3, 2, 1}};
    for(int i=0; i<3; i++){
       int pid = fork();
       if(pid == 0){
         multi(i, A, B);
       }
       else if(pid < 0){
          perror("Fork Faild.");
          exit(1);
       }
    }
    
    return 0;
}

