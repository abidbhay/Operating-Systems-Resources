#include<stdio.h>
typedef struct process{
    int burst;
    int burstrem;
    int comptime;
    int turnaround;
    int waiting;
} process;
int readyq[256];
int count=0;
void qpush( int num);
int qpop();
void main(){
    int n, curr=0, completed=0; int quantum; int curr_task=-1;
    int iscomplete[10]={0};
    int inqueue[10]= {0};
    process p[10];
    float avgtat;
    float avgwat;

	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the time quantum: ");
	scanf("%d", &quantum);
	printf("Enter burst time for each process: \n");
	for (int i=0; i<n; i++){
	    scanf("%d", &p[i].burst);
	    p[i].burstrem=p[i].burst;
	}
	if(readyq[0]==0 && curr_task==-1){
            curr_task=0;
            qpush(curr_task);
        }
    while (completed!=n){

        curr_task=qpop();
        inqueue[curr_task]=0;

        if(p[curr_task].burstrem>quantum){
            curr=curr+quantum;
            p[curr_task].burstrem=p[curr_task].burstrem-quantum;
        }
        else{
            curr=curr+p[curr_task].burstrem;
            p[curr_task].burstrem=0;
        }

        for(int i=0; i<n; i++){
            if(i!=curr_task && inqueue[i]==0 && iscomplete[i]==0){
                qpush(i); inqueue[i]=1;
            }
        }
        if(p[curr_task].burstrem!=0){
            inqueue[curr_task]=1;
            qpush(curr_task);
        }


        if(p[curr_task].burstrem==0){
            iscomplete[curr_task]=1;
            p[curr_task].comptime=curr;
            p[curr_task].turnaround= curr ;
            p[curr_task].waiting= p[curr_task].turnaround - p[curr_task].burst;
            completed++;
        }

    }
    float sum1; float sum2;

    for(int i=0; i<n;i++){

        sum1+=p[i].turnaround;
        sum2+=p[i].waiting;

    }
    avgtat=sum1/n;
    avgwat=sum2/n;
    printf("Average turnaround time: %0.3f\n", avgtat);
    printf("Average waiting time: %0.3f\n", avgwat);



}






void qpush( int num){
    if (count==256){
        fprintf(stderr,"Queue overflow!\n");
    }
    readyq[count]=num; count++;
}
int qpop(){
    if(count==0){
        fprintf(stderr,"No elements to pop!\n");
        return -1;
    }
    int res= readyq[0]; int i;
    for(i=0; i<count-1; i++){
        readyq[i]=readyq[i+1];
    } readyq[count]=0;
    count--; return res;
}
