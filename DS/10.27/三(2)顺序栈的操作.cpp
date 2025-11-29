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
    
    printf("初始化栈...\n");
    if (InitStack(&myStack) == OK) {
        printf("栈初始化成功！初始容量: %d\n", myStack.stacksize);
    } else {
        printf("栈初始化失败！\n");
        return -1;
    }

    printf("\n将元素 10, 20, 30 依次入栈...\n");
    Push(&myStack, 10);
    Push(&myStack, 20);
    Push(&myStack, 30);
    printf("入栈完成。\n");

    printf("\n开始出栈操作...\n");
    SElemType popped_element;
    while (Pop(&myStack, &popped_element) == OK) {
        printf("出栈元素: %d\n", popped_element);
    }
    
    printf("栈已空。\n");

    if (Pop(&myStack, &popped_element) == ERROR) {
        printf("\n尝试对空栈进行出栈操作失败，这是预期的行为。\n");
    }

    free(myStack.base);
    myStack.base = NULL;
    myStack.top = NULL;

    return 0;
}