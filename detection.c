#include<stdio.h>
#include<stdlib.h>
#define MAX_PROCESSES 100
#define MAX_RESOURCES 100
int num_processes;
int num_resources;
int available[MAX_RESOURCES];
int request[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];

int is_safe()
{
    int i,j;
    int avai_resources[MAX_RESOURCES];
    int state[MAX_PROCESSES];
    for(i=0;i<num_resources;i++)
    {
        avai_resources[i]=available[i];
    }
    for(i=0;i<num_processes;i++)
    {
        state[i]=0;
    }
    int found=1;
    while(found)
    {
        found=0;
        for(i=0;i<num_processes;i++)
        {
            if(!state[i])
            {
                int can_finish=1;
                for(j=0;j<num_resources;j++)
                {
                    if(request[i][j]>avai_resources[j])
                    {
                        can_finish=0;
                        break;
                    }
                }
                if(can_finish)
                {
                    found=1;
                    state[i]=1;
                    for(j=0;j<num_resources;j++)
                    {
                        avai_resources[j]+=allocation[i][j];
                    }
                }
            }
        }
    }
    for(i=0;i<num_processes;i++)
    {
        if(!state[i])
        {
            return 0;
        }
    }
}
void detect_deadlock()
{
    if(is_safe())
    {
        printf("No deadlock detected \n");
    }
    else
    {
        printf("Deadlock detected \n");
    }
}

int main()
{
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);
    printf("Enter the available resources: ");
    for (i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }
    printf("Enter the allocation matrix:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }
    printf("Enter the request matrix:\n");
    for (i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }
    detect_deadlock();

    return 0;
}
