#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void main()
{
    int n,done=0;
    float mov=0;
    printf("Enter total no. of requests : ");
    scanf("%d",&n);
    int req[n],pos;
    printf("Enter current position of head : ");
    scanf("%d",&pos);
    printf("Enter request queue : ");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&req[i]);
    }
    printf("\nSeek sequence : ");
    for(int i=0; i<n; i++)
    {
        mov=mov+abs(pos-req[i]);
        pos=req[i];
        done++;
        if(done==n)
        {
            printf("%d\n",req[i]);
        }
        else 
        {
            printf("%d -> ",req[i]);
        }
    }
    printf("Total Seek operations : %.0f\n",mov);
    printf("Average Seek Length : %.2f\n",mov/n);
}
