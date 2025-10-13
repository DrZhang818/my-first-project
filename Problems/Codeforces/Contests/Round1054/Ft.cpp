#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int solve(int h, int d) {
    int ans = d;
    if(h == 1) {
        h++;
        ans += 1;
    }

    auto ck = [&](int x) -> bool {
        int ave = d / (x + 1);
        int rem = d % (x + 1);
        ll tot = h + x;
        ll need = 1LL * (1 + ave) * ave / 2 * (x + 1);
        need += 1LL * (ave + 1) * (rem);
        return need <= tot - 1;
    };

    int l = -1, r = d;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }

    ans += r;

    return ans;
}
map<PII,int> mp;
int solve2(int h, int d) {
    auto dfs = [&](this auto &&self, int hp, int dis) -> int {
        if(dis == 0) {
            return -1;
        }
        if(hp == 1) {
            return 1 + self(hp + 1, dis);
        }
        if(mp.contains({hp, dis})) {
            return mp[{hp, dis}];
        }
        int ans = 2 * inf + 1;
        for(int i = 1; i <= dis; i++) {
            ll need = 1LL * (1 + i) * i / 2;
            if(hp - need <= 0) break;
            ans = min(ans, self(hp - need + 1, dis - i) + i + 1);
        }
        return mp[{hp, dis}] = ans;
    };
    return dfs(h, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int d = 3; d <= 100; d++) {
        for(int h = 1; h <= 50; h++) {
            int ans1 = solve(h, d);
            int ans2 = solve2(h, d);
            if(ans1 != ans2) {
                cerr << h << " " << d << " : " << ans1 << " " << ans2 << "\n";
            }
        }
    }
    return 0;
}
