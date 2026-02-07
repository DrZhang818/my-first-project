#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int q;
    cin >> q;
    int cur = 0, tag = 0;
    while(q--) {
        int A;
        cin >> A;
        if(A == 1) {
            cur++;
        } else if(A == 2) {
            cur = max(0, cur - 1);
        } else {
            tag ^= 1;
        }
        if(cur >= 3 && tag) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
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
