#include <stdio.h>

int a[200005], pre1[200005], pre2[200005];
void solve() {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    pre1[0] = 0;
    pre2[0] = 0;
    for (int i = 2; i <= n; i++) {
        pre1[i] = pre1[i - 1] + (a[i - 1] < a[i]);
        pre2[i] = pre2[i - 1] + (a[i - 1] > a[i]);
    }
    while (q--) {
        int l, r;
        scanf("%d %d", &l, &r);
        printf("%d %d\n", pre1[r] - pre1[l], pre2[r] - pre2[l]);
    }
}
int main() {
    int t = 1;
    while (t--) {
        solve();
    }
    return 0;
}
