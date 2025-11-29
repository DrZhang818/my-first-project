#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0

typedef int Elemtype;
typedef int Status;

typedef struct Snode {
    Elemtype data;
    struct Snode *next;
} Snode, *LinkStack;

Status Push(LinkStack *Top, Elemtype x);
Status Pop(LinkStack *Top, Elemtype *e);

Status Push(LinkStack *Top, Elemtype x) {
    LinkStack t = (LinkStack)malloc(sizeof(Snode));
    if (t == NULL) {
        return ERROR; 
    }
    t->data = x;
    t->next = *Top;
    *Top = t;
    return OK;
}

Status Pop(LinkStack *Top, Elemtype *e) {
    if (*Top == NULL) {
        return ERROR; 
    }
    LinkStack q = *Top;
    *Top = (*Top)->next;
    *e = q->data;
    free(q);
    return OK;
}

int main() {
    LinkStack myStack = NULL;
    
    for(int i = 1; i <= 10; i++) {
        Push(&myStack, i);
    }
    Elemtype popped_element;
    while(Pop(&myStack, &popped_element) == OK) {
        printf("Popped element: %d\n", popped_element);
    }

    return 0;
}