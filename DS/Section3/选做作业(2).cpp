#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int n;
    char a, b, c;
    int op;
} Info;

int main() {
    int n;
    scanf("%d", &n);

    Info *stk = (Info *)malloc((1 << n + 1) * sizeof(Info));
    int top = 0;

    stk[top++] = (Info){n, 'A', 'B', 'C', 0};

    while(top) {
        Info t = stk[--top];
        if(t.n == 0) continue;
        if(t.op == 1) {
            printf("%d %c %c\n", t.n, t.a, t.c);
        } else {
            stk[top++] = (Info){t.n - 1, t.b, t.a, t.c, 0};
            stk[top++] = (Info){t.n, t.a, t.b, t.c, 1};
            stk[top++] = (Info){t.n - 1, t.a, t.c, t.b, 0};
        }
    }    

    return 0;
}
