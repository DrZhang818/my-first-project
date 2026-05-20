#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 2E9;

struct Info {
    int l, r, x;
    friend bool operator<(const Info& a, const Info& b) {
        return a.l < b.l;
    }
};

struct Node {
    int v, r;
    friend bool operator<(const Node& a, const Node& b) {
        if(a.v != b.v) {
            return a.v > b.v;
        }
        return a.r > b.r;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<Info> a(m);
    for(int i = 0; i < m; i++) {
        cin >> a[i].l >> a[i].r >> a[i].x;
    }
    sort(a.begin(), a.end());

    string ans;    
    priority_queue<Node> q;
    int bias = 0;
    for(int i = 1, j = 0; i <= n; i++) {
        while(j < m && a[j].l <= i) {
            q.push(Node(a[j].r - a[j].x + 1 - bias, a[j].r));
            j++;
        }
        while(!q.empty() && q.top().r < i) {
            q.pop();
        }
        if(!q.empty() && q.top().v + bias == i) {
            cout << 1 << " \n"[i == n];
            bias++;
        } else {
            cout << 0 << " \n"[i == n];
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
