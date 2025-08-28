#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct AhoCorasick {
    static const int ALPHABET = 26;
    struct node {
        int len;
        int link;
        array<int, ALPHABET> next;
        int cnt;
        node() : len{0}, link{0}, next{}, cnt{0} {}
    };

    vector<node> t;

    AhoCorasick() {
        init();
    }

    void init() {
        t.assign(2, node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const string &a) {
        int p = 1;
        for(auto c : a) {
            int x = c - 'a';
            if(t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }

    void work() {
        queue<int> q;
        q.push(1);

        while(!q.empty()) {
            int x = q.front();
            q.pop();

            for(int i = 0; i < ALPHABET; i++) {
                if(t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    int next(int p, int x) {
        return t[p].next[x];
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
};

void solve() {
    string s;
    cin >> s;
    AhoCorasick ac;
    int q;
    cin >> q;
    vector<int> id(q + 1);
    for(int i = 1; i <= q; i++) {
        string t;
        cin >> t;
        id[i] = ac.add(t);
    }
    ac.work();
    int sz = ac.size();
    vector<vector<int>> adj(sz);
    for(int i = 2; i < sz; i++) {
        adj[ac.link(i)].push_back(i);
    }
    vector<int> cnt(sz);
    for(int i = 0, p = 1; i < s.size(); i++) {
        int x = s[i] - 'a';
        p = ac.next(p, x);
        cnt[p]++;
    }
    auto dfs = [&](auto &&self, int u) -> void {
        for(int v : adj[u]) {
            self(self, v);
            cnt[u] += cnt[v];
        }
    };
    dfs(dfs, 1);
    for(int i = 1; i <= q; i++) {
        cout << cnt[id[i]] << "\n";
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
