/*Implement the multi-level feedback queue scheduling algorithm by considering the following diagram: 
You can use the code of others to implement Roud-Robin, and FCFS but implement aging by your own self.*/

#include<stdio.h>

struct g
{
    char name;
    int AT,BT,WT,TAT,RT,CT;//AT-Arrival time,BT-Burst time,Tat-Turn around time,RT-Response time,Ct-Completion time
}
a[10],b[10],d[10];//Three queues for multilevel implementation(array)

int n;

void sorting()
{
struct g temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(a[i].AT>a[j].AT)//swapping
                    {
                          temp=a[i];
                          a[i]=a[j];
                          a[j]=temp;
                    }
            }
    }
}


int main()
{
     int i,j,k=0,r=0,time=0,t1=5,t2=8,flag=0;//declaration of variables
     char c;
     
     printf("Enter no of processes:");
     scanf("%d",&n);//input for number of variables
     
     for(i=0,c='A';i<n;i++,c++)//for multiple inputs
     {
         a[i].name=c;
         printf("\nEnter the arrival time and burst time of process %c: ",a[i].name);
         scanf("%d%d",&a[i].AT,&a[i].BT);
         a[i].RT=a[i].BT;//save burst time in remaining time for each process

    }
sorting();//to arrange

time=a[0].AT;
printf("first queue with RR with qt=5");//1st queue with quantum time 5 with round robin


printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
for(i=0;i<n;i++)
{

  if(a[i].RT<=t1)
  {

       time+=a[i].RT;//from arrival time of first process to completion of this process
       a[i].RT=0;
       a[i].WT=time-a[i].AT-a[i].BT;//amount of time process has been waiting in the first queue
       a[i].TAT=time-a[i].AT;//amount of time to execute the process
       printf("\n%c\t\t%d\t\t%d\t\t%d",a[i].name,a[i].BT,a[i].WT,a[i].TAT);//printing values

  }
  else//process moves to queue 2 with quantum time=8
  {
      b[k].WT=time;
      time+=t1;
      b[i].RT-=t1;
      b[k].BT=a[i].RT;
      b[k].RT=b[k].BT;
      b[k].name=a[i].name;
      k=k+1;
      flag=1;//it is imp to enter the second queue
   }
}


if(flag==1)//if condition is true in previous else it enters the second queue which has quantum time 8
 {
 printf("\nProcess in second queue following RR with qt=8");
 printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
}

for(i=0;i<k;i++)
   {
    if(b[i].RT<=t2)
     {
       time+=b[i].RT;//from arrival time of first process +BT of this process
       b[i].RT=0;
       b[i].WT=time-t1-b[i].BT;//amount of time process has been waiting in the ready queue
       b[i].TAT=time-b[i].AT;//amount of time to execute the process
       printf("\n%c\t\t%d\t\t%d\t\t%d",b[i].name,b[i].BT,b[i].WT,b[i].TAT);

    }
    else//process moves to queue 3 with First come first serve
    {
      d[r].AT=time;//tranfering the necessary info to third queue
      time+=t2;
      b[i].RT-=t2;
      d[r].BT=d[i].RT;
      d[r].RT=d[r].BT;
      d[r].name=d[i].name;
      r=r+1;
      flag=2;
    }
  }


if(flag==2)
{
printf("\nProcess in third queue(FCFS)");
}
for(i=0;i<r;i++)//appplying first come first serve
{
    if(i==0)
            d[i].CT=d[i].BT+time-t1-t2;
        else
            d[i].CT=d[i-1].CT+d[i].BT;

}

for(i=0;i<r;i++)
    {
        d[i].TAT=d[i].CT;//turaround time
        d[i].WT=d[i].TAT-d[i].BT;//waiting time formula
        printf("\n%c\t\t%d\t\t%d\t\t%d\t\t",d[i].name,d[i].BT,d[i].WT,d[i].TAT);//printing the information

    }

}  
