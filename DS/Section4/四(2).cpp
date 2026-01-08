#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 255
typedef unsigned char SString[MAXLEN + 1];

void assign(SString T, const char* chars) {
    int len = strlen(chars);
    if(len > MAXLEN) len = MAXLEN;
    T[0] = len;
    for (int i = 1; i <= len; i++) T[i] = chars[i - 1];
}

void getNext(SString T, int *next) {
    int i = 1, j = 0;
    next[1] = 0;
    while(i < T[0]) {
        if(j == 0 || T[i] == T[j]) {
            ++i; ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int Index_KMP(SString S, SString T, int pos, int *next) {
    int i = pos, j = 1;
    while(i <= S[0] && j <= T[0]) {
        if (j == 0 || S[i] == T[j]) {
            ++i; ++j;
        } else {
            j = next[j]; 
        }
    }
    return (j > T[0]) ? i - T[0] : 0;
}

int main() {
    SString S, T;
    char s[MAXLEN], t[MAXLEN];

    scanf("%s", s);
    scanf("%s", t);
    assign(S, s);
    assign(T, t);

    int next[MAXLEN + 1];
    getNext(T, next);

    printf("next: ");
    for(int i = 1; i <= T[0]; i++) {
        printf("%d ", next[i]);
    }
    printf("\n");

    int res = Index_KMP(S, T, 1, next);
    printf("res: %d\n", res);

    return 0;
}