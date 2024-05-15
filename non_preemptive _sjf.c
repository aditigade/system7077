#include<stdio.h>
#include<stdlib.h>
struct node
{
    int process,AT,BT,CT,WT,TAT,priority,vis;
};
struct link
{
    struct node data;
    struct link *next;
};
struct link *head=NULL;
void insert(struct node t)
{
    struct link *temp=head;
    struct link *newnode = (struct link *)malloc(sizeof(struct link));
    newnode->data=t;
    newnode->next=NULL;
    if(head==NULL)
    {
        head=newnode;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
    }
}
void Delete(int p)
{
    struct link *temp=head, *prevnode=head;
    while(temp->data.process!=p)
    {
        prevnode=temp;
        temp=temp->next;
    }
    if(temp==head)
    {
        head=head->next;
        free(temp);
    }
    else
    {
        prevnode->next=temp->next;
        free(temp);
    }
}
void priorityBased(struct node arr[], int n)
{
    struct node gChart[n];
    struct link *temp, *minPrio;
    int done=0,t=0;
    float totalWT=0,totalTAT=0;
    printf("PID\tAT\tBT\tPrio\tCT\tWT\tTAT\n");
    while(done!=n)
    {
        for(int i=0; i<n; i++)
        {
            if(arr[i].AT<=t && arr[i].vis==0)
            {
                insert(arr[i]);
                arr[i].vis=1;
            }
        }
        temp=head,minPrio=head;
        while(temp!=NULL)
        {
            if(temp->data.priority < minPrio->data.priority)
            {
                minPrio=temp;
            }
            temp=temp->next;
        }
        temp=minPrio;
        if(temp!=NULL){
        t=t+temp->data.BT;
        temp->data.CT=t;
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",temp->data.process,temp->data.AT,temp->data.BT,temp->data.priority,temp->data.CT,temp->data.CT-temp->data.AT-temp->data.BT,temp->data.CT-temp->data.AT);
        totalWT=totalWT+temp->data.CT-temp->data.AT-temp->data.BT;
        totalTAT=totalTAT+temp->data.CT-temp->data.AT;
        gChart[done].process=temp->data.process;
        gChart[done].CT=t;
        Delete(temp->data.process);
        done++;
        }
        else
        {
            t++;
        }
    }
    printf("\n\nGantt Chart : ");
    for(int i=0; i<n; i++)
    {
        printf("%d ",gChart[i].process);
    }
    printf("\n\nAverage WT : %.2f",totalWT/n);
    printf("\nAverage TAT : %.2f",totalTAT/n);
}
void main()
{
    int n;
    printf("Enter no. of process : ");
    scanf("%d",&n);
    struct node arr[n];
    for(int i=0; i<n; i++)
    {
        printf("Enter process id : ");
        scanf("%d",&arr[i].process);
        printf("Enter AT : ");
        scanf("%d",&arr[i].AT);
        printf("Enter BT : ");
        scanf("%d",&arr[i].BT);
        printf("Enter priority : ");
        scanf("%d",&arr[i].priority);
        arr[i].vis=0;
    }
    printf("\n");
    priorityBased(arr,n);
}
