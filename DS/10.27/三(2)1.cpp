#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int SElemType;
typedef int Status;

typedef struct {
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack *S);
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);

Status InitStack(SqStack *S) {
    S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S->base) {
        exit(OVERFLOW);
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return OK;
}

Status Push(SqStack *S, SElemType e) {
    if (S->top - S->base >= S->stacksize) {
        S->base = (SElemType *)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S->base) {
            exit(OVERFLOW);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e) {
    if (S->top == S->base) {
        return ERROR;
    }
    *e = *--S->top;
    return OK;
}

int main() {
    SqStack myStack;
    InitStack(&myStack);

    for(int i = 1; i <= 10; i++) {
        Push(&myStack, i);
    }
    
    SElemType popped_element;
    while (Pop(&myStack, &popped_element) == OK) {
        printf("Popped element: %d\n", popped_element);
    }

    free(myStack.base);
    myStack.base = NULL;
    myStack.top = NULL;

    return 0;
}