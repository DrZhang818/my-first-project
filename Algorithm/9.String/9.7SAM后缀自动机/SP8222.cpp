#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

struct SAM {
    static constexpr int ALPHABET_SIZE = 26;
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

void chmax(int &x, int y) {
    if(x < y) {
        x = y;
    }
}

void solve() {
    string s;
    cin >> s;
    SAM sam;
    for(int p = 1; char c : s) {
        p = sam.extend(p, c);
    }
    int n = sam.size() - 1;
    vector adj(n + 1, vector<int>{});
    for(int i = 2; i <= n; i++) {
        adj[sam.link(i)].push_back(i);
    }
    int m = s.size();
    vector<int> dp(m + 1);
    vector<int> cnt(n + 1);
    auto dfs = [&](auto &&self, int u) -> void {
        cnt[u] = sam.count(u);
        for(int v : adj[u]) {
            self(self, v);
            cnt[u] += cnt[v];
        }
        chmax(dp[sam.len(u)], cnt[u]);
    };
    dfs(dfs, 1);
    for(int i = m - 1; i >= 1; i--) {
        chmax(dp[i], dp[i + 1]);
    }
    for(int i = 1; i <= m; i++) {
        cout << dp[i] << "\n";
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
