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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<ll> val;
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            val.push_back(pre[j] - pre[i - 1]);
        }
    }
    ll ans = 0;
    for(int s = 59; s >= 0; s--) {
        vector<ll> nval;
        int c = 0;
        for(ll x : val) {
            if(x >> s & 1) {
                c++;
                nval.push_back(x);
            } 
        }
        if(c >= k) {
            ans |= 1LL << s;
            swap(val, nval);
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
