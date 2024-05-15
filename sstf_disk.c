#include<stdio.h>
#include<math.h>
void main()
{
    int pos,n,done=0;
    float mov=0;
    printf("Enter current head position : ");
    scanf("%d",&pos);
    printf("Enter no. of requests : ");
    scanf("%d",&n);
    int req[n];
    printf("Enter request queue : ");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&req[i]);
    }
    int min,minIndex;
    printf("\nSeek sequence : ");
    while(done<n)
    {
        min=req[0],minIndex=0;
        for(int i=0; i<n; i++)
        {
            if(req[i]<min)
            {
                min=req[i];
                minIndex=i;
            }
        }
        mov=mov+abs(min-pos);
        pos=min;
        req[minIndex]=999;
        done++;
        if(done==n)
        {
            printf("%d\n",min);
        }
        else
        {
            printf("%d -> ",min);
        }
    }
    printf("Total seek operations : %.0f",mov);
    printf("\nAverage seek length : %.2f\n",mov/n);
}
