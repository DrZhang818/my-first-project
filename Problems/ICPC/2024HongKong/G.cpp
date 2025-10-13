#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct node {
    array<int,26> to;
    int cnt;
};

vector<vector<int>> fac;
void init(int n) {
    fac.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j += i) {
            fac[j].push_back(i);
        }
    }
}

void solve() {
    int n;
    cin >> n;

    vector<node> tr;
    auto newnode = [&]() {
        tr.emplace_back(node());
        return tr.size() - 1;
    };
    int rt = newnode();

    vector<ll> w(n + 1);
    ll ans = 0;

    auto update = [&](int cnt) {
        for(int x : fac[cnt]) {
            ans ^= w[x] * x;
            w[x]++;
            ans ^= w[x] * x;
        }
    };

    auto add = [&](string &s) -> int {
        int cur = rt;
        tr[rt].cnt++;
        for(char c : s) {
            int x = c - 'a';
            if(tr[cur].to[x] == 0) {
                tr[cur].to[x] = newnode();
            }
            cur = tr[cur].to[x];
            tr[cur].cnt++;
            update(tr[cur].cnt);
        }
        return cur;
    };

    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        int cur = add(s);
        cout << ans << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init(500001);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
