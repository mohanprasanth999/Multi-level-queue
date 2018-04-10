#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
int n,i,j,r=0,k=0,q=0,t,flag,flag1;
void roundrobin();
void preemptive();
void sort();
typedef struct Process
{
    int pid, burst,arrival,prior;

}process;
process p[200],q1[200],q2[200];
void Arrival_sorting()
{

      process temp;
      for(i = 0; i < n - 1; i++)
      {
            for(j = i + 1; j < n; j++)
            {
                  if(p[i].arrival> p[j].arrival)
                  {
                        temp = p[i];
                        p[i] = p[j];
                        p[j] = temp;
                  }
            }
      }
      int s;
      for(s=0;s<n;s++)
      {
          if(p[s].arrival==p[s+1].arrival&&p[s].prior>p[s+1].prior)
            {
                temp = p[s+1];
                p[s+1] = p[s];
                p[s] = temp;
            }
      }
}
void sort()
{
    process temp1;
    for(i = 0; i < n - 1; i++)
      {
            for(j = i + 1; j < n; j++)
            {
                  if(p[i].prior> p[j].prior)
                  {
                        temp1 = p[i];
                        p[i] = p[j];
                        p[j] = temp1;
                  }
                  if(q2[i].prior>q2[j].prior)
                  {
                        temp1 = q2[i];
                        q2[i] = q2[j];
                        q2[j] = temp1;
                  }
            }
      }
}
void preemptive()
{
    int c=n,a=0,flag=0;
    t=p[0].arrival;
   while(t>=0&&c>0)
   {
        if (p[k].arrival < p[k+1].arrival&&p[k].burst>0)
           {
               printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].prior);
               p[k].burst=p[k].burst-1;
               if(p[k].burst==0&&p[k+1].prior < p[k].prior&&p[k+1].arrival > p[k].arrival&&p[k+1].arrival==t)
                {
                    k=k+1;
                    c--;
                }
                else if(p[k].burst==0)
                    c--;
           }

        else if (p[k].arrival == p[k+1].arrival && p[k].prior<p[k+1].prior&&p[k].burst>0)
                {
                    printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].prior);
                    p[k].burst=p[k].burst-1;
                    if(p[k].burst==0)
                          c--;
                }
        else if(k==n-1&&p[k].burst>0)
            {
                printf("Process P%d is Running at time %d with priority %d \n",p[k].pid,t,p[k].prior);
                p[k].burst=p[k].burst-1;
                if(p[k].burst==0)
                 {
				 
				 c--;

                 }
                 if(c!=n-1&&c!=0&&p[k].burst==0||(c==1&&p[k].burst==0))
                 {
                     int l,m;
                     for(l=0;l<n;l++)
                        {
                            sort();
                            if(p[l].burst==q2[l].burst)
                            {
                                for(m=0;p[l].burst>0;m++)
                            {
                                t++;
                                printf("Process %d is running at time %d with priority %d\n",p[i].pid,t,p[i].prior);
                                p[l].burst=p[l].burst-1;
                                if(p[l].burst==0)
                                  c--;
                            }
                            }
                        }
                        c=0;
                 }
            }
            else if(c!=0&&c!=n-1)

                {
                    flag1=1;
                    roundrobin();
                    if(p[k+1].prior<p[k].prior&&p[k].arrival>=t)
                    k=k+1;
                    if(k!=n-1&&p[k].arrival>t)
                        {
                            t=p[k].arrival;
                            t--;
                        }
                }
            ++t;
            for(a=k+1;a<n;a++)
            {
                if(p[a].arrival==t&&flag==0)
               {
                if(p[a].prior < p[k].prior&&p[a].arrival > p[k].arrival||(p[a].prior==p[k+1].prior||p[a].prior==p[k].prior)&&p[a].arrival>p[k+1].arrival||p[a].arrival>p[k].arrival)//if priority and arrival time both are same
                   {
                       if(p[k].burst>0)
                       {
                       q1[q]=p[k];
                       q++;
                       r++;
                       c--;
                       }
                       k=a;
                       flag=1;
                   }
               }
            }
            flag=0;
   }
}
void roundrobin()
{
    int f=0,f1=0,r1=0,x=r,flag2=0;  if(flag1==1)
     while(t>0&&x>0&&p[k+1].arrival>t&&flag2==0)
    {
        if(flag2==0)
                {
                    if(q1[r1].burst>0)
                    {
                    printf("Queue1 Process P%d is running at time %d with priority %d\n",q1[r1].pid,t,q1[r1].prior);
                    q1[r1].burst=q1[r1].burst-1;
                    t++;
                    if(p[k+1].arrival==t)
                        {flag2==1;
                        t=p[k+1].arrival;
                            t--;
                            goto b;}

                    if(q1[r1].burst==0)
                      {
                         x--;
                         if(x==0)
                            r--;
                      }
                    }
                    ++f;
                    if(f>=2)
                    {
                        if(r1<x)
                            ++r1;
                        else
                            r1=0;
                        f=0;
                    }
                }
    }

     if(flag1==0)
       while(t>0&&r>0)
    {
            if(flag2==0)
                {
                    if(q1[r1].burst>0)
                    {
                    printf("Process P%d is running at time %d with priority %d\n",q1[r1].pid,t,q1[r1].prior);
                    q1[r1].burst=q1[r1].burst-1;
                    t++;
                    if(q1[r1].burst==0)
                        r--;
                    }
                    ++f1;
                    if(f1>=2)
                    {
                        if(r1<r)
                            ++r1;
                        else
                            r1=0;
                        f1=0;
                    }
                }
    }
    b: printf("");
}
int main()
{

    printf("--------------------------------------------------------------------------\n");
    printf("                      MULTILEVEL QUEUE SCHEDULING                  \n");
    printf("--------------------------------------------------------------------------\n");
    printf("Enter the no.of process\n");
    scanf("%d",&n);
    for(i =0;i<n;i++)
    {
        fflush(stdin);
        printf("Enter Process %d: \n",i);
        printf("Enter Burst Time In Multiples Of 2: (for e.g. 2,4...etc)\n");
        scanf("%d",&p[i].burst);
        printf("Arrival Time:\n");
        scanf("%d",&p[i].arrival);
        printf("Priority:\n");
        scanf("%d",&p[i].prior);
        p[i].pid=i;
    }
    Arrival_sorting();
    for(i=0;i<n;i++)
    {
        q2[i]=p[i];
    }
     for(i=0;i<n;i++)
    {
        printf("Process P%d: Burst %d arrival:%d Priority:%d\n",i+1,p[i].burst,p[i].arrival,p[i].prior);
    }
    preemptive();
    int x1=r;
    flag1=0;
    roundrobin();
    for(i=0;i<x1;i++)
    {
        printf("Process Q%d: burst %d arrival:%d prior:%d\n",i+1,q1[i].burst,q1[i].arrival,q1[i].prior);
    }
    return 0;
}
