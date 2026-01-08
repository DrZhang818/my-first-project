#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct stack {
    char stk[100];
    int idx = 0;
    void push(char c) {
        stk[++idx] = c;
    }
    void pop() {
        idx--;
    }
    char top() {
        if(idx == 0) {
            return '#';
        }
        return stk[idx];
    }
    bool empty() {
        return idx == 0;
    }
} stack ;

int main() {

    int n;
    scanf("%d", &n);
    char s[100];
    scanf("%s", s);
   
    stack stk;
    for(int i = 0; i < n; i++) {
        if(s[i] == ')') {
            if(!stk.empty() && stk.top() == '(') {
                stk.pop();
                continue;
            }
        } else if(s[i] == ']') {
            if(!stk.empty() && stk.top() == '[') {
                stk.pop();
                continue;
            }
        } else if(s[i] == '}') {
            if(!stk.empty() && stk.top() == '{') {
                stk.pop();
                continue;
            }
        }
        stk.push(s[i]);
    }

    if(stk.empty()) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}
