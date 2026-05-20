#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    priority_queue<int, vector<int>, greater<int>> pq;
    while(n--) {
        int op, h;
        cin >> op >> h;
        if(op == 1) {
            pq.push(h);
        } else {
            while(!pq.empty() && pq.top() <= h) {
                pq.pop();
            }
        }
        cout << pq.size() << "\n";
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
