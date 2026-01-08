#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    priority_queue<int> A, B;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        A.push(x);
    }
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        B.push(x);
    }
    int s = 1;
    while(!A.empty() && !B.empty()) {
        int x = A.top(), y = B.top();
        if(s) {
            B.pop();
            if(y > x) {
                B.push(y - x);
            }
        } else {
            A.pop();
            if(x > y) {
                A.push(x - y);
            }
        }
        s ^= 1;
    }
    if(!A.empty()) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
