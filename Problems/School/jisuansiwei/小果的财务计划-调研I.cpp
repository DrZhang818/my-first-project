#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    priority_queue<int> q0, q1;
    int x;
    ll tot = 0;
    while(cin >> x) {
        if(x > 0) {
            q1.push(x);
        } else if(x < 0) {
            q0.push(-x);
        }
        tot += x;
    }
    cout << tot << "\n";
    for(int i = 0; i < 3 && !q0.empty(); i++) {
        cout << -q0.top() << " ";
        q0.pop();
    }
    cout << "\n";
    for(int i = 0; i < 3 && !q1.empty(); i++) {
        cout << q1.top() << " ";
        q1.pop();
    }
    cout << "\n";
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
