#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void SumofPC(int n){
    int pid = fork();
    int sumOdd = 0, sumEven =  0;
    if(pid == 0){
      for(int i=1; i<=n; i+=2){
         sumOdd = sumOdd+i;
      }
      printf("Sum of odd number in Child process:%d\n", sumOdd);
    }
    else if(pid == -1){
       perror("Fork failed.\n");
       exit(1);
    }
    else{
       for(int i=2; i<=n; i+=2){
          sumEven = sumEven+i;
       }
       printf("Sum of even number in parent process:%d\n",sumEven);
    }
    
}

int main(void){
    int n;
    printf("Enter a number:");
	scanf("%d", &n);
	SumofPC(n);
    return 0;
}
