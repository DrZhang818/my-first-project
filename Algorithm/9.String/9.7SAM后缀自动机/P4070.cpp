#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct SAM {
    struct Node {
        int len;
        int link;
        int cnt;
        map<int,int> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    vector<Node> t;
    SAM(int n) {
        init(n);
    }
    void init(int n) {
        t.assign(2, Node());
        t[0].len = -1;
        t.reserve(n * 2 + 5);
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if(p == 0) {
            t[p].next[c] = 1;
        }
        if(t[p].next.contains(c)) {
            int q = t[p].next[c];
            if(t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while(t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
                if(p == 0) {
                    t[p].next[c] = 1;
                }
            }
            return r;
        }
        int cur = newNode();
        t[cur].cnt = 1;
        t[cur].len = t[p].len + 1;
        while(!t[p].next.contains(c)) {
            t[p].next[c] = cur;
            p = t[p].link;
            if(p == 0) {
                t[p].next[c] = 1;
            }
        }
        t[cur].link = extend(p, c);
        return cur;
    }    
    int extend(int p, char c, char offset = 'a') {
        return extend(p, c - offset);
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int next(int p, char c, char offset = 'a') {
        return next(p, c - 'a');
    }

    int link(int p) {
        return t[p].link;
    }

    int len(int p) {
        return t[p].len;
    }

    int size() {
        return t.size();
    }

    int count(int p) {
        return t[p].cnt;
    }
};

void solve() {
    int n;
    cin >> n;
    SAM sam(n);
    ll ans = 0;
    for(int i = 1, p = 1; i <= n; i++) {
        int x;
        cin >> x;
        p = sam.extend(p, x);
        ans += sam.len(p) - sam.len(sam.link(p));
        cout << ans << "\n";
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
