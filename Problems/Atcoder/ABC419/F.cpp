#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
bool is_suf(const string &s, const string &t) {
    if(s.size() < t.size()) {
        return false;
    }
    for(int i = s.size() - 1, j = t.size() - 1; i >= 0 && j >= 0; i--, j--) {
        if(s[i] != t[j]) {
            return false;
        }
    }
    return true;
}
void solve() {
    int n, L;
    cin >> n >> L;
    vector<string> ss(n);
    for(int i = 0; i < n; i++) {
        cin >> ss[i];
    }
    int c = 0;
    unordered_map<string,int> mp;
    mp[""] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= ss[i].size(); j++) {
            string s = ss[i].substr(0, j);
            if(mp.find(s) == mp.end()) {
                mp[s] = ++c;
            }
        }
    }
    vector<int> msk(c + 1);
    for(auto &[s, idx] : mp) {
        int bit = 0;
        for(int j = 0; j < n; j++) {
            if(is_suf(s, ss[j])) {
                bit |= 1 << j;
            }
        }
        msk[idx] = bit;
    }
    vector<vector<int>> nxt(c + 1);
    for(auto &[s, idx] : mp) {
        for(char c = 'a'; c <= 'z'; c++) {
            string t = s + c;
            for(int j = 0; j <= t.size(); j++) {
                string cur = t.substr(j);
                if(mp.find(cur) != mp.end()) {
                    nxt[idx].push_back(mp[cur]);
                    break;
                }
            }
        }
    }
    vector dp(c + 1, vector<int>(1 << n));
    dp[0][0] = 1;
    for(int i = 0; i < L; i++) {
        vector ndp(c + 1, vector<int>(1 << n));
        for(int j = 0; j <= c; j++) {
            for(int s = 0; s < 1 << n; s++) {
                if(dp[j][s]) {
                    for(int k : nxt[j]) {
                        add(ndp[k][s | msk[k]], dp[j][s]);
                    }
                }
            }
        }
        swap(dp, ndp);
    }
    int ans = 0;
    for(int i = 0; i <= c; i++) {
        add(ans, dp[i][(1 << n) - 1]);
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
