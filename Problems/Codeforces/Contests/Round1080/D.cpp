#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll sum = a[1] + a[n];
    sum /= (n - 1);

    vector<ll> ans(n + 1);
    ll pre = 0, presum = 0;
    for(int i = 1; i < n; i++) {
        ans[i] = (a[i + 1] + a[n] - sum * (n - i - 1)) / 2 - pre - presum;
        presum += ans[i];
        pre += presum;
    }
    ans[n] = sum - presum;
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
