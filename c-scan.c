#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void main()
{
    int pos,n,done=0,t;
    float mov=0;
    printf("Enter initial position of head : ");
    scanf("%d",&pos);
    int ipos=pos;
    printf("Enter total no. of requests : ");
    scanf("%d",&n);
    printf("Enter total no. of tracks : ");
    scanf("%d",&t);
    int req[n];
    printf("Enter request queue : ");
    for(int i=0; i<n; i++)
    {
        scanf("%d",&req[i]);
    }
    printf("\nSeek sequence : ");
    for(int i=pos; i<t; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(req[j]==i)
            {
                mov=mov+abs(req[j]-pos);
                pos=req[j];
                done++;
                if(done==n)
                {
                    printf("%d\n",req[j]);
                }
                else
                {
                    printf("%d -> ",req[j]);
                }
                req[j]=999;
            }
        }
    }
    if(pos!=t-1)
    {
        mov=mov+(t-1)-pos;
        pos=t-1;
    }
    mov=mov+t-1;
    pos=0;
    for(int i=0; i<ipos; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(req[j]==i)
            {
                mov=mov+abs(req[j]-pos);
                pos=req[j];
                done++;
                if(done==n)
                {
                    printf("%d\n",req[j]);
                }
                else
                {
                    printf("%d -> ",req[j]);
                }
                req[j]=999;
            }
        }
    }
    printf("Total no. of seek operations : %.0f",mov);
    printf("\nAverage seek length : %.2f\n",mov/n);
}
