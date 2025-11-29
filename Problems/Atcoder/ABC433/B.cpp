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
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1, -1);
    stack<int> stk;
    for(int i = 1; i <= n; i++) {
        while(!stk.empty() && a[i] >= a[stk.top()]) {
            stk.pop();
        }
        if(!stk.empty()) {
            pre[i] = stk.top();
        }
        stk.push(i);
    }
    for(int i = 1; i <= n; i++) {
        cout << pre[i] << "\n";
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
