#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> c(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        c[i] = a[i] / b[i];
        sum += c[i];
    } 
    vector<int> ans(n + 1);
    if(sum >= k) {
        for(int i = 1; i <= n; i++) {
            sum -= c[i];
            ans[i] = max(0LL, k - sum);
            k -= ans[i];
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
