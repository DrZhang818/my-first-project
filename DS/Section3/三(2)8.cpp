#include <stdio.h>
#include <stdlib.h>

int q[1000005];
int f[1000005];

int rear = 0;
int n;
void fib(int k, int max) {
    for(int i = 0; i <= k - 2; i++) {
        f[i] = 0;
        q[rear++] = 0;
    }
    n = k;
    q[rear++] = 1;
    while(q[rear] < max) {
        f[n] = 0;
        for(int j = 0; j < k; j++) {
            f[n] += q[j];
        }
        rear = (rear + 1) % k;
        q[rear] = f[n];
        n++;
    }
    if(q[rear] > max) {
        n -= 2;
    } else {
        n -= 1;
    }
    if(max == 1) {
        n = k;
        f[k] = 1;
    }
}

int main() {

    int k, max;
    scanf("%d %d", &k, &max);
    fib(k, max);
    for(int i = 0; i <= n; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");
    return 0;
}