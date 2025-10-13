#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> pre0(n + 1), pre1(n + 1);
    for(int i = 1; i <= n; i++) {
        pre0[i] = pre0[i - 1] + (a[i] == 0);
        pre1[i] = pre1[i - 1] + (a[i] == 1);
    }
    vector<int> las(n + 1);
    for(int L = -1, R = 1; R <= n; R++) {
        if(a[R] == a[R - 1]) {
            las[R] = R - 1; 
            L = R - 1;
        } else {
            las[R] = L;
        }
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        int c0 = pre0[r] - pre0[l - 1];
        int c1 = pre1[r] - pre1[l - 1];
        if((r - l + 1) % 3 != 0 || c0 % 3 != 0 || c1 % 3 != 0) {
            cout << -1 << "\n";
            continue;
        }
        int ans = (r - l + 1) / 3;
        if(las[r] < l) {
            ans += 1;
        }
        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
