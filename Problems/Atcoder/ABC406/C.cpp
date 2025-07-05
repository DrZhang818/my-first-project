#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc406/tasks/abc406_c
/*
    思维


*/

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> d;
    int cur = 0, tag = (a[2] > a[1] ? 0 : 1);
    for(int i = 2; i <= n; i++) {
        if(!tag && a[i] > a[i - 1] || tag && a[i] < a[i - 1]) {
            cur++;
        } else {
            tag ^= 1;
            d.push_back(cur);
            cur = 1;
        }
    }
    d.push_back(cur);
    ll ans = 0;
    for(int i = (a[2] > a[1] ? 1 : 2); i + 1 < d.size(); i += 2) {
        ans += (ll)d[i - 1] * d[i + 1];
    }
    cout << ans << "\n";
}

void solve2() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre1(n + 1), pre2(n + 1);
    for(int i = 2; i < n; i++) {
        pre1[i] = pre1[i - 1] + (a[i] > a[i - 1] && a[i] > a[i + 1]);
        pre2[i] = pre2[i - 1] + (a[i] < a[i - 1] && a[i] < a[i + 1]);
    }
    pre1[n] = pre1[n - 1], pre2[n] = pre2[n - 1];
    ll ans = 0;
    int c1 = 0, c2 = 0;
    for(int i = 1; i <= n - 3; i++) {
        if(a[i] >= a[i + 1]) continue;
        c1 = pre1[i], c2 = pre2[i];
        int l, r = n;
        auto it = lower_bound(pre2.begin() + i, pre2.end(), c2 + 1);
        if(it == pre2.end()) break;
        l = it - pre2.begin() + 1;
        it = lower_bound(pre1.begin() + i, pre1.end(), c1 + 2);
        if(it != pre1.end()) r = it - pre1.begin();
        ans += r - l + 1;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
