#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct node {
    int cnt {};
    array<int,2> nxt {};
};

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for(int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i];
    }
    vector<node> tr;
    auto add = [&]() -> int {
        tr.push_back(node());
        return tr.size() - 1;
    };
    int rt = add();
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            ll sum = pre[j] - pre[i - 1];
            int cur = rt;
            for(int s = 60; s >= 0; s--) {
                int pop = sum >> s & 1;
                if(tr[cur].nxt[pop] == 0) {
                    tr[cur].nxt[pop] = add();
                }
                cur = tr[cur].nxt[pop];
                tr[cur].cnt++;
            }
        }
    }
    ll ans = 0;
    int cur = rt;
    for(int s = 60; s >= 0; s--) {
        int nxt = -1, tag = -1;
        if(tr[cur].nxt[1] == 0) {
            nxt = tr[cur].nxt[0];
            tag = 0;
        } else if(tr[cur].nxt[0] == 0) {
            nxt = tr[cur].nxt[1];
            tag = 1;
        } else {
            if(tr[tr[cur].nxt[1]].cnt >= k) {
                nxt = tr[cur].nxt[1];
                tag = 1;
            } else {
                nxt = tr[cur].nxt[0];
                tag = 0;
            }
        }
        cur = nxt;
        cerr << cur << " " << tr[cur].cnt << "\n";
        // assert(tr[cur].cnt >= k);
        ans += ll(tag) << s;
    }
    cout << ans << "\n";
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
