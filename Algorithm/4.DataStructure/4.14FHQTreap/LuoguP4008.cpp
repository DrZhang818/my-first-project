#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct FHQ {
    struct Node {
        int l = 0, r = 0;
        char v;
        int sz = 0;
        unsigned int p = 0;
    };
    
    vector<Node> tr;
    int root = 0;

    FHQ(int n = 0) {
        tr.reserve(n + 1);
        tr.push_back({0, 0, 0, 0, 0});
    }

    int newNode(int v) {
        tr.push_back({0, 0, v, 1, (unsigned int)rng()});
        return tr.size() - 1;
    }

    void pull(int u) {
        tr[u].sz = tr[tr[u].l].sz + tr[tr[u].r].sz + 1;
    }

    void split(int u, int k, int &x, int &y) {
        if(!u) {
            x = y = 0;
            return;
        }
        if(tr[tr[u].l].sz + 1 <= k) {
            x = u;
            split(tr[u].r, k - tr[tr[u].l].sz - 1, tr[u].r, y);
        } else {
            y = u;
            split(tr[u].l, k, x, tr[u].l);
        }
        pull(u);
    }

    int merge(int u, int v) {
        if(!u || !v) return u | v;
        if(tr[u].p > tr[v].p) {
            tr[u].r = merge(tr[u].r, v);
            pull(u);
            return u;
        } else {
            tr[v].l = merge(u, tr[v].l);
            pull(v);
            return v;
        }
    }

    int build(int n, const string &s) {
        stack<int> stk;
        for(int i = 0; i < n; i++) {
            int u = newNode(s[i]);
            int last = 0;
            while(!stk.empty() && tr[stk.top()].p < tr[u].p) {
                pull(stk.top());
                last = stk.top();
                stk.pop();
            }
            if(!stk.empty()) tr[stk.top()].r = u;
            tr[u].l = last;
            stk.push(u);
        }
        int res = 0;
        while(!stk.empty()) {
            res = stk.top();
            pull(res);
            stk.pop();
        }
        return res;
    }

    void print(int u) {
        if(!u) return;
        print(tr[u].l);
        cout << tr[u].v;
        print(tr[u].r);
    }
};

void solve() {  
    int q;
    cin >> q;
    FHQ tr;
    int pos = 0;
    while(q--) {
        string s;
        cin >> s;
        if(s[0] == 'M') {
            cin >> pos;
        } else if(s[0] == 'I') {
            int n;
            cin >> n;
            string s;
            char c;
            while(s.size() < n) {
                cin.get(c);
                if(32 <= c && c <= 126) {
                    s += c;
                }
            }
            int x, y;
            tr.split(tr.root, pos, x, y);
            tr.root = tr.merge(tr.merge(x, tr.build(n, s)), y);
        } else if(s[0] == 'D') {
            int n;
            cin >> n;
            int x, y, z;
            tr.split(tr.root, pos, x, y);
            tr.split(y, n, y, z);
            tr.root = tr.merge(x, z);
        } else if(s[0] == 'G') {
            int n;
            cin >> n;
            int x, y, z;
            tr.split(tr.root, pos, x, y);
            tr.split(y, n, y, z);
            tr.print(y);
            cout << "\n";
            tr.merge(x, tr.merge(y, z));
        } else if(s[0] == 'P') {
            pos--;
        } else if(s[0] == 'N') {
            pos++;
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
