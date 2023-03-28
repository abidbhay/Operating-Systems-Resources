#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdbool.h>


void* func( void* arg){
	int num= *(int*)arg;
	for(int i=2; i<num; i++){
		if(num%2==0) pthread_exit("Not prime");
	}
	pthread_exit("Prime");
}

int main(){
	char* threadreturn;
	pthread_t thread;
	int num= 19;
	pthread_create(&thread, NULL, (void*) func, (void*)&num);
	pthread_join(thread,(void**)&threadreturn);
	printf("The number is %s\n", threadreturn);

return 0;
}
