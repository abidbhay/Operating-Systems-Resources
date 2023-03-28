#include<stdio.h>
#include<math.h>
typedef struct process{
    int burst;
    int burstrem;
    int arrival;
    int comptime;
    int turnaround;
    int waiting;
    int p;
} process;


int main(){
    int n=4, curr=0, completed=0; int min; int curr_task;
    int iscomplete[10]={0};
    process p[10];
    float avgtat;
    float avgwat;

	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter arrival time, burst and priority: \n");
	for (int i=0; i<n; i++){
	    scanf("%d %d %d", &p[i].arrival,&p[i].burst, &p[i].p);
	    p[i].burstrem=p[i].burst;
	}
    while (completed!=n){
        min=100000;
        curr_task=-1;
        for(int i=0; i<n; i++){  //searching for new process
            if (p[i].arrival<=curr && iscomplete[i]==0 && p[i].burstrem!=0){
                if(p[i].p<min){
                    curr_task=i;
                    min=p[i].p;
                }
                /*
                else if(p[i].priority==min){
                   if(p[curr_task].arrival>p[i].arrival) {
                        curr_task=i;
                   }
                }
                */
            } //arrived and not complete

        }
        curr++;
        p[curr_task].burstrem--;
        if(p[curr_task].burstrem==0){
            iscomplete[curr_task]=1;
            p[curr_task].comptime=curr;
            p[curr_task].turnaround= curr - p[curr_task].arrival;
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



return 0;}
