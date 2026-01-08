#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 255
typedef unsigned char SString[MAXLEN + 1];

void assign(SString T, const char* chars) {
    int len = strlen(chars);
    if(len > MAXLEN) len = MAXLEN;
    T[0] = len;
    for(int i = 1; i <= len; i++) {
        T[i] = chars[i - 1];
    }
}

int Index(SString S, SString T, int pos) {
    int i = pos, j = 1;
    while(i <= S[0] && j <= T[0]) {
        if(S[i] == T[j]) {
            ++i; ++j;
        } else {
            i = i - j + 2; 
            j = 1;
        }
    }
    return (j > T[0]) ? i - T[0] : 0;
}

int Index_FL(SString S, SString T, int pos) {
    int sLen = S[0], tLen = T[0];
    int i = pos;
    char patStart = T[1], patEnd = T[tLen];

    while(i <= sLen - tLen + 1) {
        if(S[i] != patStart) {
            ++i;
        } else if(S[i + tLen - 1] != patEnd) {
            ++i;
        } else {
            int k = 1, j = 2;
            while(j < tLen && S[i + k] == T[j]) {
                ++k; ++j;   
            }
            if(j == tLen) return i;
            ++i;
        }
    }
    return 0;
}

int main() {
    SString S, T;
    char s[MAXLEN], t[MAXLEN];

    scanf("%s", s);
    scanf("%s", t);
    assign(S, s);
    assign(T, t);

    int res1 = Index(S, T, 1);
    int res2 = Index_FL(S, T, 1);

    printf("res1: %d\n", res1);
    printf("res2: %d\n", res2);

    return 0;
}