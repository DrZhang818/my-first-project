#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

int solve1(vector<int> a) {
    int n = a.size() - 1;
    vector<map<int,int>> dp(n + 1);
    dp[0][0] = 1;
    for(int i = 1; i <= n; i++) {
        int cur = a[i];
        for(int j = i - 1; j >= 0; j--) {
            for(auto [x, c] : dp[j]) {
                if(x <= cur) {
                    add(dp[i][cur], c);
                }
            }
            cur |= a[j];
        }
    }
    int ans = 0;
    for(auto [x, c] : dp[n]) {
        add(ans, c);
    }
    return ans;
}

int solve2(vector<int> a) {
    int n = a.size() - 1;
    vector<map<int,int>> dp(n + 1), psum(n + 1);
    dp[0][-inf] = 1, psum[0][-inf] = 1;
    for(int i = 1; i <= n; i++) {
        int cur = a[i];
        int x = -1;
        for(int j = i - 1; j >= 0; j--) {
            auto it = psum[j].upper_bound(cur);
            if(it != psum[j].begin()) {
                it = prev(it);
                add(dp[i][cur], it->second);
            }
            if((a[j] | a[i]) == a[j]) {
                x = a[j];
                break;
            }
            a[j] |= a[i];
            cur = a[j];
        }
        if(x != -1) {
            for(auto &[y, c] : dp[i - 1]) {
                if(y >= x) {
                    add(dp[i][y], c);
                }
            }
        }
        int S = 0;
        for(auto &[y, c] : dp[i]) {
            add(S, c);
            psum[i][y] = S;
        }
    }
    int ans = psum[n].rbegin()->second;
    return ans;
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n = 100, V = 234324;
    for(int T = 0; T < 10000; T++) {
        vector<int> a(n + 1);
        for(int i = 1; i <= n; i++) {
            a[i] = get(0, V);
        }
        int ans1 = solve1(a);
        int ans2 = solve2(a);
        if(ans1 != ans2) {
            cerr << "WA!\n";
            for(int i = 1; i <= n; i++) {
                cerr << a[i] << " \n"[i == n];
            }
            cerr << "std: " << ans1 << " now: " << ans2 << "\n";
        } 
    }



    return 0;
}
