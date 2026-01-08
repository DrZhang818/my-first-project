#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXSIZE 10

typedef int Elemtype;
typedef int Status;

typedef struct {
    Elemtype *Queue;
    int Front;
    int Rear;
} Sequeuetp ;

Status InitQueue(Sequeuetp *Q) {
    Q->Queue = (Elemtype *)malloc(MAXSIZE * sizeof(Elemtype));
    if(!Q->Queue) {
        exit(EXIT_FAILURE);
    }
    Q->Front = 0;
    Q->Rear = 0;
    return OK;
}

Status Encycque(Sequeuetp *Q, Elemtype x) {
    if((Q->Rear + 1) % MAXSIZE == Q->Front) {
        return ERROR;
    }
    Q->Queue[Q->Rear] = x;
    Q->Rear = (Q->Rear + 1) % MAXSIZE;
    return OK;
}

Status Decycque(Sequeuetp *Q, Elemtype *e) {
    if(Q->Front == Q->Rear) {
        return ERROR;
    } 
    *e = Q->Queue[Q->Front];
    Q->Front = (Q->Front + 1) % MAXSIZE;
    return OK;
}

int main() {
    Sequeuetp q;
    InitQueue(&q);

    for(int i = 1; i <= 5; i++) {
        Encycque(&q, i);
    }

    Elemtype e;
    while(Decycque(&q, &e) != ERROR) {
        printf("Dequeued element: %d\n", e);
    }
    printf("\n");

    return 0;
}