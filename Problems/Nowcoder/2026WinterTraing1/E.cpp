#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    deque<int> q;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        q.push_back(x);
    }
    int mx = -inf;
    for(int i = 1; i <= n + 1; i++) {
        mx = max(mx, q.front() + k);
        int t = q.back();
        q.pop_back();
        q.push_front(k);
        k = t;
    }
    cout << mx << "\n";
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
