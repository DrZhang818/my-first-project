#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

struct Info {
    int l, r;
};

void solve() {
    int n;
    cin >> n;
    vector<Info> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i].l >> a[i].r;
    }

    sort(a.begin(), a.end(), 
        [&](auto& x, auto& y) {
            return x.l < y.l;
        });

    int idx = -inf;
    priority_queue<int, vector<int>, greater<int>> pq;

    int i = 0;
    while(i < n || !pq.empty()) {
        while(i < n && a[i].l <= idx) {
            pq.push(a[i].r);
            i++;
        }
        if(pq.empty()) {
            idx = a[i].l;
            continue;
        }
        if(pq.top() < idx) {
            cout << "No\n";
            return;
        }
        pq.pop();
        idx++;
    }

    cout << "Yes\n";
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
