#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 2000000000;

struct info {
    int cnt = 0;
    int dp = inf;
    int v = 0;
    array<int,2> to{0, 0};
};

void solve() {
    int q;
    cin >> q;
    vector<info> tr;
    int rt = 0;
    vector<int> p;
    auto add = [&]() -> int {
        tr.push_back(info());
        p.push_back(0);
        return tr.size() - 1;
    };
    auto update = [&](int x, int d) -> void {
        int cur = rt;
        for(int i = 30; i >= 0; i--) {
            int s = x >> i & 1;
            if(tr[cur].to[s] == 0) {
                int t = add();
                tr[cur].to[s] = t;
                p[t] = cur;
            }
            cur = tr[cur].to[s];
            tr[cur].cnt += d;
            if(tr[cur].cnt == 1) {
                tr[cur].v = s << i;
            } else {
                tr[cur].v = 0;
            }
        }
        while(cur != rt) {
            int u = tr[cur].to[0];
            int v = tr[cur].to[1];
            if(tr[u].cnt > tr[v].cnt) {
                swap(u, v);
            }
            if(tr[u].cnt <= 1 && tr[v].cnt <= 1) {
                tr[cur].dp = tr[cur].v ^ tr[u].dp ^ tr[v].dp;
            } else if(tr[u].cnt <= 1 && tr[v].cnt >= 2) {
                tr[cur].dp = tr[v].dp;
            } else {
                tr[cur].dp = min(tr[u].dp, tr[v].dp);
            }
            cur = p[cur];
        }
    };
    rt = add();
    tr[rt].dp = 0;
    while(q--) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            update(x, 1);
        } else if(op == 2) {
            int x;
            cin >> x;
            update(x, -1);
        } else {
            int res = inf;
            if(tr[tr[rt].to[0]].cnt) {
                res = min(res, tr[tr[rt].to[0]].dp);
            }
            if(tr[tr[rt].to[1]].cnt) {
                res = min(res, tr[tr[rt].to[1]].dp);
            }
            cout << res << "\n";
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
