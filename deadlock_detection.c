#include <stdio.h>
#include <stdlib.h>


int main()
{
    printf("Enter number of processes");
    int n;
    scanf("%d",&n);
    int m;
    printf("Enter number of resources ");
    scanf("%d",&m);
    int allocate[n][m];
    int request[n][m];
    int available[m];
    printf("Enter each process and its resource allocation \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&allocate[i][j]);
        }
    }
    printf("Enter the request matrix now \n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            scanf("%d",&request[i][j]);
        }
    }
    printf("the entered allocate matrix is \n");
    for(int i=0;i<n;i++)
    {
        for(int j =0;j<m;j++)
        {
            printf("%d",allocate[i][j]);
        }
        printf("\n");
    }
    printf("the entered request matrix is \n");
    for(int i=0;i<n;i++)
    {
        for(int j =0;j<m;j++)
        {
            printf("%d",request[i][j]);
        }
        printf("\n");
    }
    int instance[m];
    printf("Enter resource instances ");
    for(int i=0;i<m;i++)
    scanf("%d",&instance[i]);
    int sum[m];
    for(int i=0;i<m;i++)
    sum[i] = 0;
    for(int k=0;k<m;k++)
    {
    for(int i=0;i<n;i++)
    {
        sum[k] += allocate[i][k];
    }
    }
    for(int i=0;i<m;i++)
    available[i]=instance[i]-sum[i];
    printf("The available matrix is \n");
    for(int i =0;i<m;i++)
    printf("%d",available[i]);
    int flag=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(request[i][j]>available[j])
            {
                flag=1;
                break;
            }
            else
            continue;
        }
    }
    if(flag==1)
    printf("\n Deadlock detected");
    else
    printf("\n No deadlock detected");
    return 0;
}
