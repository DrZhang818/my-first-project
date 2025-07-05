#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1798/D
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), pos, neg;
    bool ok = false;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] != 0) {
            ok = true;
        }
        if(a[i] < 0) {
            neg.push_back(a[i]);
        } else {
            pos.push_back(a[i]);
        }
    }
    if(!ok) {
        cout << "No\n";
        return;
    }
    vector<int> ans(n + 1);
    ll cur = 0;
    for(int i = 1; i <= n; i++) {
        if(cur < 0) {
            ans[i] = pos.back();
            pos.pop_back();
        } else {
            if(!neg.empty()) {
                ans[i] = neg.back();
                neg.pop_back();
            } else {
                ans[i] = pos.back();
                pos.pop_back();
            }
        }
        cur += ans[i];
    }
    cout << "Yes\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
