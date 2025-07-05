#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int sz = 0;
    map<int,int> son;
};
vector<info> tr;
int nxt(int u, int v) {
    int res = 0;
    if(!tr[u].son.count(v)) {
        tr.push_back(info());
        tr[u].son[v] = tr.size() - 1;
    } 
    res = tr[u].son[v];
    return res;
}
void add(string &s) {
    int cur = 0, n = s.size();
    for(int i = 0; i < n; i++) {
        int c = s[i];
        cur = nxt(cur, c);
        tr[cur].sz++;
    }
}
int query(string &s) {
    int cur = 0, n = s.size();
    for(int i = 0; i < n; i++) {
        int c = s[i];
        if(!tr[cur].son.count(c)) return 0;
        cur = tr[cur].son[c];
    }
    return tr[cur].sz;
}
void solve() {
    int n, q;
    cin >> n >> q;
    tr.clear();
    tr.push_back(info());
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        add(s);
    }
    while(q--) {
        string s;
        cin >> s;
        cout << query(s) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
