#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define MAXQSIZE 10

typedef int Elemtype;
typedef int Status;

typedef struct {
    Elemtype *Queue;
    int Front;
    int Rear;
} Sequeuetp ;

Status InitQueue(Sequeuetp *Q) {
    Q->Queue = (Elemtype *)malloc(MAXQSIZE * sizeof(Elemtype));
    if(!Q->Queue) {
        exit(EXIT_FAILURE);
    }
    Q->Front = 0;
    Q->Rear = 0;
    return OK;
}

Status Enqueue(Sequeuetp *Q, Elemtype x) {
    if(Q->Rear == MAXQSIZE) {
        return ERROR;
    } else {
        Q->Queue[Q->Rear] = x;
        Q->Rear++;
        return OK;
    }
}

Status Dequeue(Sequeuetp *Q, Elemtype *e) {
    if(Q->Front == Q->Rear) {
        return ERROR;
    } else {
        *e = Q->Queue[Q->Front];
        Q->Front++;
        return OK;
    }
}

int main() {
    Sequeuetp q;
    InitQueue(&q);

    for(int i = 1; i <= 5; i++) {
        Enqueue(&q, i);
    }

    Elemtype e;
    while(Dequeue(&q, &e) != ERROR) {
        printf("Dequeued element: %d\n", e);
    }
    printf("\n");

    return 0;
}