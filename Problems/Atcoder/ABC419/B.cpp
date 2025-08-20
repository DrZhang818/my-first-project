#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int qq;
    cin >> qq;
    priority_queue<int, vector<int>, greater<int>> q;
    while(qq--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            q.push(x);
        } else {
            int x = q.top();
            q.pop();
            cout << x << "\n";
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
