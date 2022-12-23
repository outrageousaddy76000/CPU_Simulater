#include <stdio.h>
#include <stdlib.h>

struct queue{
    int id;
    int run_time;
    int priority; 
    struct queue *next;
};

struct queue *front = NULL;
struct queue *rear = NULL;
struct queue *front2 = NULL;
struct queue *rear2 = NULL;

void enqueue(struct queue **front, struct queue **rear, int idp, int rtp, int pri){
    struct queue *newnode=(struct queue*)malloc(sizeof(struct queue*));
    struct queue *ptr = NULL;
    struct queue *temp1 = *front;
    struct queue *temp2 = *rear;
    struct queue *ins_before = NULL;
    newnode->id = idp;
    newnode->run_time=rtp;
    newnode->priority=pri;
    newnode->next = NULL;
    ptr = newnode;
    if(*front==NULL){
        *front = ptr;
        *rear = ptr;
    }
    else {
        //insert based on priority in ascending order
        int check=1;
        while(check){
            if(temp1->priority>pri){
                ins_before=temp1;
                break;
            }
            if(temp1->next==NULL) 
            check=0;
            temp1=temp1->next;
        }
        if(ins_before==NULL){
            //insert at the end
            temp2->next = ptr;
            *rear = ptr;
        }
        else{
            //insert before the ins_before pointer
            struct queue *insert = *front;
            if(insert = ins_before){
                //insert at the beginning
                newnode->next = ins_before;
                *front = newnode;
                return;
            }
            while(insert->next!=ins_before){
                insert = insert->next;
            }
            newnode->next=ins_before;
            insert->next = ptr;
        }
    }
}

void dequeue(struct queue **front,int time){
    struct queue *ptr = *front;
    struct queue *ret = *front;
    ptr = ptr->next;
    *front = ptr;
    printf("Process id : %d\nExectution time : %d\n",ret->id,time);
}

int size(struct queue **front,struct queue **rear){
    int l=0;
    struct queue *temp=*front;
    if(temp==NULL) return 0;
    while(temp->next!=NULL){
        l++;
        temp=temp->next;
    }
    return l+1;
}

int main()
{
    int slice,in_process;
    printf("Enter the time slice : ");
    scanf("%d",&slice);
    printf("Enter initial number of processes : ");
    scanf("%d",&in_process);
    while(in_process--){
        int idp,rtp,pri;
        printf("Enter id of process : ");
        scanf("%d",&idp);
        printf("Enter run time of process : ");
        scanf("%d",&rtp);
        printf("Enter priority of process : ");
        scanf("%d",&pri);
        enqueue(&front,&rear,idp,rtp,pri);
    }
    int time=0;
    while(size(&front,&rear)){
        int insize = size(&front,&rear);
        struct queue *temp=NULL;
        temp=front;
        while(insize--){
            time+=slice;
            if(temp->run_time - slice <= 0){
                dequeue(&temp,time);
            }
            else {
                enqueue(&front2,&rear2,temp->id,(temp->run_time)-slice,temp->priority);
                temp=temp->next;
            }
        }
        front = NULL;
        rear = NULL;
        int repsize = size(&front2,&rear2);
        temp = front2;
        while(repsize--){
            enqueue(&front,&rear,temp->id,temp->run_time,temp->priority);
            temp=temp->next;
        }
        front2 = NULL;
        rear2 = NULL;
        int pro;
        printf("Enter the number of processes you want to add : ");
        scanf("%d",&pro);
        while(pro--){
            int idp,rtp,pri;
            printf("Enter id of process : ");
            scanf("%d",&idp);
            printf("Enter run time of process : ");
            scanf("%d",&rtp);
            printf("Enter priority of process : ");
            scanf("%d",&pri);
            enqueue(&front,&rear,idp,rtp,pri);
        }
    }
    printf("All processes complete!");
    return 0;
}