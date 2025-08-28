#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int L = 1;
    int cnt = 0;
    ll ans = 0;
    vector<int> c(n + 1);
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 1) {
            cnt++;
            stk.push(i);
            c[i] = 1;
            ans += cnt;
        } else {
            while(!stk.empty()) {
                int u = stk.top();
                if(c[u] == a[i] - 1) {
                    c[u] = a[i];
                    break;
                } else {
                    stk.pop();
                    cnt--;
                }
            }
            ans += cnt;
        }
    }
    cout << ans << "\n";
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
