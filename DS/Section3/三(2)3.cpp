#include <stdio.h>
#include <stdlib.h>

#define stacksize 100

typedef struct {
    int base[stacksize];
    int top;
} stack ;

int push(stack *s, int e) {
    if(s->top >= stacksize) {
        return 0;
    }
    s->base[s->top++] = e;
    return 1;
}

int pop(stack *s, int *e) {
    if(s->top == 0) {
        return 0;
    }
    *e = s->base[--s->top];
    return 1;
}

int main() {
    stack s1;

    int m, e, n;
    s1.top = 0;
    m = 1348;
    n = 8;

    while(m) {
        push(&s1, m % n);
        m /= n;
    }

    while(s1.top != 0) {
        pop(&s1, &e);
        printf("%d", e);
    }
    printf("\n");

    return 0;
}