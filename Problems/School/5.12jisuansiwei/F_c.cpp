#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int stk[100005];
long long a[100005], pre[100005], suf[100005];
int top = 0;
void solve() {
    int n;
    scanf("%d", &n);
    top = 0;
    for(int i = 1; i <= n; i++) {
        pre[i] = 0;
        suf[i] = n + 1;
    }
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for(int i = 1; i <= n; i++) {
        while(top > 0 && a[stk[top]] >= a[i]) {
            suf[stk[top]] = i;
            top--;
        }
        if(top > 0) {
            pre[i] = stk[top];
        }
        stk[++top] = i;
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        if((suf[i] - pre[i] - 1) * a[i] > ans) {
            ans = (suf[i] - pre[i] - 1) * a[i];
        }
    }
    printf("%lld\n", ans);
}

int main()
{
    int t = 1;
    // scanf("%d", &t);
    while(t--) {
        solve();
    }
    return 0;
}
