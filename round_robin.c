#include<stdio.h>
#include<stdlib.h>
struct node
{
    int process,AT,BT,WT,CT,TAT,vis,tempCT,oBT;
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
    struct link *newnode=(struct link *)malloc(sizeof(struct link));
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
void Delete(int t)
{
    struct link *prevnode=head, *temp=head;
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
    float totalWT=0,totalTAT=0;
    int n,q;
    printf("Enter number of process : ");
    scanf("%d",&n);
    printf("Enter time quantum : ");
    scanf("%d",&q);
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
        arr[i].oBT=arr[i].BT;
    }
    int k=-1;
    struct node gChart[20];

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            struct node temp=arr[j];
            if(arr[j].AT>arr[j+1].AT)
            {
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    printf("PID\tAT\tBT\tCT\tWT\tTAT\n");
    int t=0,done=-1;
    int time;
    struct node value;
    do{
    for(int i=0; i<n; i++)
    {
        if(arr[i].AT<=t && arr[i].vis==0)
        {
            arr[i].vis=1;
            insert(arr[i]);
        }
    }
    struct link *temp=head;
    if(temp->data.BT>q)
    {
        t=t+q;
        k++;
        gChart[k].process=temp->data.process;
        gChart[k].tempCT=t;
        temp->data.BT=temp->data.BT-q;
        time=temp->data.BT;
        value=temp->data;
        Delete(gChart[k].process);
    }
    else
    {
        t=t+temp->data.BT;
        k++;
        temp->data.BT=0;
        time=temp->data.BT;
        value=temp->data;
        gChart[k].process=temp->data.process;
        gChart[k].CT=t;
        temp->data.CT=t;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",temp->data.process,temp->data.AT,temp->data.oBT,temp->data.CT,temp->data.CT-temp->data.AT-temp->data.oBT,temp->data.CT-temp->data.AT);
        totalWT=totalWT+temp->data.CT-temp->data.AT-temp->data.oBT;
        totalTAT=totalTAT+temp->data.CT-temp->data.AT;
        Delete(gChart[k].process);
        done++;
    }
    for(int i=0; i<n; i++)
    {
        if(arr[i].AT<=t && arr[i].vis==0)
        {
            arr[i].vis=1;
            insert(arr[i]);
        }
    }

    if(time>0)
    {
        insert(value);
    }
    }while(done<n-1);
    printf("\nGant Chart : ");
    for(int i=0; i<=k; i++)
    {
        printf("%d ",gChart[i].process);
    }
    printf("\n\nAverage WT : %.2f",totalWT/n);
    printf("\nAverage TAT : %.2f",totalTAT/n);
}
