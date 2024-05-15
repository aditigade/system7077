#include<stdio.h>
#include<stdlib.h>
struct node
{
    int p;
    int AT,BT;
    int TAT,CT,WT;
};

void main()
{
    int n;
    printf("Enter no. of process : ");
    scanf("%d",&n);
    struct node arr[n];
    int pID,aT,bT;
    for(int i=0; i<n; i++)
    {
        printf("Enter process id : ");
        scanf("%d",&pID);
        arr[i].p=pID;
        printf("Enter AT : ");
        scanf("%d",&aT);
        arr[i].AT=aT;
        printf("Enter BT : ");
        scanf("%d",&bT);
        arr[i].BT=bT;
    }
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
    int T=arr[0].AT;//time array maintained to keep track of time
    float totalWT=0, totalTAT=0;
    for(int i=0; i<n; i++)
    {
        arr[i].WT=T-arr[i].AT;
        arr[i].TAT=arr[i].BT+arr[i].WT;
        arr[i].CT=arr[i].TAT+arr[i].AT;
        T=T+arr[i].BT;
        totalWT=totalWT+arr[i].WT;
        totalTAT=totalTAT+arr[i].TAT;
    }
    printf("\nPID\tAT\tABT\tWT\tTAT\tCT\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",arr[i].p,arr[i].AT,arr[i].BT,arr[i].WT,arr[i].TAT, arr[i].CT);
    }
    printf("\nAverage WT : %.2f\nAverage TAT : %.2f\n",totalWT/n,totalTAT/n);
}
