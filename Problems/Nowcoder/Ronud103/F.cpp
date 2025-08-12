#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ull P = 13131;

ull pw[100005];
void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<string> ss(m + 1);
    for(int i = 1; i <= m; i++) {
        cin >> ss[i];
    }
    unordered_map<ull,ll> mp;
    for(int i = 1; i <= m; i++) {
        ull hash = 0;
        for(char c : ss[i]) {
            hash = hash * P + c;
            mp[hash]++;
        }
    }
    unordered_set<ull> vis;
    for(int i = 1; i <= m; i++) {
        ull cur = 0;
        for(char c : ss[i]) {
            ull nxt = cur * P + c;
            if(!vis.contains(nxt)) {
                mp[nxt] += mp[cur];
                vis.insert(nxt);
            }
            cur = nxt;
        }
    }
    s = "#" + s;
    vector<ull> acc(n + 1);
    for(int i = 1; i <= n; i++) {
        acc[i] = acc[i - 1] * P + s[i];
    }
    auto get = [&](int l, int r) -> ull {
        return acc[r] - acc[l - 1] * pw[r - l + 1];
    };
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int l = i - 1, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(vis.contains(get(i, mid))) {
                l = mid;
            } else {
                r = mid;
            }
        }
        if(l <= n) {
            ans = max(ans, mp[get(i ,l)]);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    pw[0] = 1;
    for(int i = 1; i <= 100000; i++) {
        pw[i] = pw[i - 1] * P;
    }
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}