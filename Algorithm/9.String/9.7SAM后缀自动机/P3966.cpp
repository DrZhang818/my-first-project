#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct SAM {
    static constexpr int ALPHABET_SIZE = 27;
    struct Node {
        int len;
        int link;
        int cnt;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, cnt{}, next{} {}
    };
    vector<Node> t;
    SAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if(t[p].next[c]) {
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
            }
            return r;
        }
        int cur = newNode();
        t[cur].cnt = 1;
        t[cur].len = t[p].len + 1;
        while(!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
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
    vector<string> s(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    SAM sam;
    for(int i = 1, p = 1; i <= n; i++) {
        for(char c : s[i]) {
            p = sam.extend(p, c);
        }
        p = sam.extend(p, char('z' + 1));
    }
    int m = sam.size() - 1;
    vector adj(m + 1, vector<int>{});
    for(int i = 2; i <= m; i++) {
        adj[sam.link(i)].push_back(i);
    }
    vector<int> cnt(m + 1);
    [&](this auto &&self, int u) -> void {
        cnt[u] = sam.count(u);
        for(int v : adj[u]) {
            self(v);
            cnt[u] += cnt[v];
        }
    } (1);
    for(int i = 1; i <= n; i++) {
        int p = 1;
        for(char c : s[i]) {
            p = sam.next(p, c);
        }
        cout << cnt[p] << "\n";
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
