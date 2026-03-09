#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    stack<int> stk;
    for(int i = 0; i < n; i++) {
        if(!stk.empty() && s[i] == s[stk.top()]) {
            stk.pop();
        } else {
            stk.push(i);
        }
    }

    if(stk.empty()) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
