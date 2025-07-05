#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, k;
    cin >> n >> k;
    priority_queue<int> q;
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        int x; cin >> x;
        q.push(x);
        tot += x;
    }
    for(int i = 0; i < k && !q.empty(); i++) {
        tot -= q.top();
        q.pop();
    }
    cout << tot << "\n";
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
