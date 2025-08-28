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
    int n;
    cin >> n;
    AhoCorasick ac;
    vector<int> id(n + 1);
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        id[i] = ac.add(s);
    }
    ac.work();
    int sz = ac.size();
    vector<bool> vis(sz);
    string s;
    cin >> s;
    for(int i = 0, p = 1; i < s.size(); i++) {
        int x = s[i] - 'a';
        p = ac.next(p, x);
        vis[p] = true;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += vis[id[i]];
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
