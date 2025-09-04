#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;

void solve() {
    int Q;
    cin >> Q;
    vector<int> a(Q + 1);
    vector<int> id(Q + 1);
    vector<int> nxt(Q + 1);

    int c = 0;
    
    auto add = [&](int pos, int v) -> void {
        a[++c] = v;
        id[v] = c;
        nxt[c] = nxt[pos];
        nxt[pos] = c;
    };

    auto query = [&](int x, int y) -> ll {
        ll sum1 = 0, sum2 = 0;
        int i = id[x], j = id[y];
        while(nxt[i] != id[y] && nxt[j] != id[x]) {
            if(nxt[i]) {
                i = nxt[i];
                sum1 += a[i];
            }
            if(nxt[j]) {
                j = nxt[j];
                sum2 += a[j];
            }
        }
        if(nxt[i] == id[y]) {
            nxt[id[x]] = id[y];
            return sum1;
        } else {
            nxt[id[y]] = id[x];
            return sum2;
        }
    };

    add(0, 0);

    for(int i = 1; i <= Q; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int x;
            cin >> x;
            add(id[x], i);
        } else {
            int x, y;
            cin >> x >> y;
            cout << query(x, y) << "\n";
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
