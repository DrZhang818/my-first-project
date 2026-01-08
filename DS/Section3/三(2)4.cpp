#include <stdio.h>
#include <stdlib.h>

#define N 8

int m = 0;
int a[N + 1];

int ok(int i, int j) {
    for(int k = 1; k < i; k++) {
        if(a[k] == j || abs(i - k) == abs(j - a[k])) {
            return 0;
        }
    }
    return 1;
}

void queen(int i) {
    if(i > N) {
        m++;
        printf("Solution %d: ", m);
        for(int k = 1; k <= N; k++) {
            printf("%d ", a[k]);
        }
        printf("\n");
    } else {
        for(int j = 1; j <= N; j++) {
            if(ok(i, j)) {
                a[i] = j;
                queen(i + 1);
            }
        }
    }
}

int main() {
    queen(1);
    return 0;
}