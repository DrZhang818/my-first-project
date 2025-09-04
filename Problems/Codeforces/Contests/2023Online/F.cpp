#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct node {
    array<int, 2> to;
    ll c1, c2;
    node() : to{0, 0}, c1{0}, c2{0} {}
};
void solve() {
    int n;
    cin >> n;
    map<ll,int> mp;
    for(int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        mp[x]++;
    }
    ll ans = 1LL * n * (n - 1) * (n - 2) / 6;
    for(auto [x, c] : mp) {
        ans -= 1LL * c * (c - 1) * (c - 2) / 6;
    }

    vector<node> tr;
    auto add = [&]() -> int {
        tr.push_back(node());
        return tr.size() - 1;
    };
    int rt = add();
    for(auto [x, c] : mp) {
        int cur = rt;
        for(int i = 0; i < 61; i++) {
            int pop = x >> i & 1;
            if(!tr[cur].to[pop]) {
                tr[cur].to[pop] = add();
            }
            if(i % 2 == 0 && tr[cur].to[pop ^ 1] != 0) {
                ans -= tr[tr[cur].to[pop ^ 1]].c2 * c;
                ans -= tr[tr[cur].to[pop ^ 1]].c1 * c * (c - 1) / 2;
            }
            cur = tr[cur].to[pop];
            tr[cur].c1 += c;
            tr[cur].c2 += 1LL * c * (c - 1) / 2;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
