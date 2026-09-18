#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;
constexpr int N = 1E6;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = s[i] == '(' || s[i] == ')';
    }
    stack<int> stk, stkf;
    vector<int> match(n, -1);

    bool flag = true;
    stkf.push(0);

    for(int i = 0; i < n; i++) {
        int x = a[i];
        if(stk.empty() || a[stk.top()] != x) {
            if(stkf.top() & (1 << x)) flag = false;
            stkf.push(0);
            stk.push(i);
        } else {
            stkf.pop();
            stkf.top() |= (1 << x);
            match[i] = stk.top();
            stk.pop();
        }
    }

    cout << (flag ? "Yes\n" : "No\n");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}