#include<stdio.h>
#include<stdlib.h>
struct node
{
    int process;
    int AT;
    int BT;
    int vis;
    int CT;
};
struct link
{
    struct node data;
    struct link *next;
};
struct link *head=NULL;
void insert(struct node t)
{
    struct link *newnode = (struct link *)malloc(sizeof(struct link));
    newnode->data=t;
    newnode->next=NULL;
    struct link *temp=head;
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
void Delete(int t)
{
    struct link *temp=head,*prevnode=head;
    while(temp->data.process!=t)
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
void main()
{
    int n;
    float waitTime=0,turnAT=0;
    printf("Enter number of process : ");
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
        arr[i].vis=0;
    }

    printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
    int k=-1,t=0;
    struct node gChart[n];
    while(k<n-1)
    {
        for(int i=0; i<n; i++)
        {
            if(arr[i].AT <= t && arr[i].vis==0)
            {
                arr[i].vis=1;
                insert(arr[i]);
            }
        }
        if(head!=NULL){
        int minBT=head->data.BT;
        struct link *temp=head, *result=head;
        while(temp!=NULL)
        {
            if(temp->data.BT<minBT)
            {
                minBT=temp->data.BT;
                result=temp;
            }
            temp=temp->next;
        }
        t=t+result->data.BT;
        k++;
        gChart[k].process=result->data.process;
        gChart[k].CT=t;
        gChart[k].AT=result->data.AT;
        gChart[k].BT=result->data.BT;
        waitTime=waitTime+gChart[k].CT-gChart[k].AT-gChart[k].BT;
        turnAT=turnAT+gChart[k].CT-gChart[k].AT;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",gChart[k].process,gChart[k].AT,gChart[k].BT,gChart[k].CT,gChart[k].CT-gChart[k].AT-gChart[k].BT,gChart[k].CT-gChart[k].AT);
        Delete(result->data.process);
        }
        else
        {
            t++;
        }
    }
    printf("\nAverage Waiting Time : %.2f\n",waitTime/n);
    printf("Average Turn Around Time : %.2f\n",turnAT/n);
}
