#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

const int inf = 1000000007;
struct info {
    int st, len, id;
    friend bool operator < (const info &a, const info &b) {
        if(a.st != b.st) return a.st > b.st;
        return a.id > b.id;
    }
};
void solve() {
    int n, m;
    cin >> n >> m;
    priority_queue<info> q1, q2;
    for(int i = 1; i <= n; i++) {
        string s;
        int age;
        info a;
        cin >> s >> age >> a.st >> a.len;
        a.id = i;
        if(age <= 60) {
            q1.push(a);
        } else {
            q2.push(a);
        }
    }
    priority_queue<int, vector<int>, greater<int>> window;
    for(int i = 1; i <= m; i++) window.push(0);
    while(n--) {
        int cur = window.top(); window.pop();
        int t1 = inf, t2 = inf;
        if(!q1.empty()) t1 = q1.top().st;
        if(!q2.empty()) t2 = q2.top().st;
        if(t2 <= max(t1, cur)) {
            window.push(max(cur, t2) + q2.top().len);
            q2.pop();
        } else {
            window.push(max(cur, t1) + q1.top().len);
            q1.pop();
        }
    }
    while(window.size() > 1) window.pop();
    cout << window.top() << "\n";
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
