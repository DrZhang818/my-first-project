#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s, t;
    cin >> s >> t;
    s = "#" + s;
    t = "#" + t;
    auto work = [&](int lo) -> ll {
        int n = s.size() - 1, m = t.size() - 1;
        vector lcp(n + 2, vector<int>(n + 2));
        vector lcs(n + 1, vector<int>(m + 1));
        for(int i = n; i >= 1; i--) {
            for(int j = n; j >= 1; j--) {
                if(s[i] == s[j]) {
                    lcp[i][j] = lcp[i + 1][j + 1] + 1;
                } 
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                if(s[i] == t[j]) {
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                } 
            }
        }
        vector pre(n + 1, vector<int>(n + 2));
        for(int i = 1; i <= n; i++) {
            auto &sum = pre[i];
            for(int j = 1; j <= m; j++) {
                sum[1]++;
                sum[lcs[i][j] + 1]--;
            }
            for(int i = 1; i <= n; i++) {
                sum[i] += sum[i - 1];
            }
            for(int i = 1; i <= n; i++) {
                sum[i] += sum[i - 1];
            }
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = i + 1; j <= n + 1; j++) {
                int lx = lo, rx = lcp[i][j];
                if(rx < lx) continue;
                auto &sum = pre[j - 1];
                int ly = max(1, j - i - rx);
                int ry = j - i - lx;
                ans += sum[ry] - sum[ly - 1];
            }
        }
        return ans;
    };
    ll ans = work(0);
    swap(s, t);
    ans += work(1);
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
