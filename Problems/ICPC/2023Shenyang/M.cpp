#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int N = 1000000;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int dp[N + 1];

int fast_pow(int a, int b) {
    int res = 1;
    while(b) {
        if(b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

const int inv3 = fast_pow(3, MOD - 2);

int get(int i) {
    return 1LL * ((fast_pow(4, i + 1) - 4) % MOD + MOD) % MOD * inv3 % MOD;
}

void solve() {
    string s, t;
    int k;
    cin >> s >> t >> k;
    reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    for(int i = 0, j = 0; i < s.size(); i++, j++) {
        if(j == t.size()) {
            t += '0';
        }
        t[j] ^= (s[i] - '0');
    }
    if(t.size() % 2) {
        t += '0';
    }
    if(t.find('1') == string::npos) {
        cout << get(k - 1) << "\n";
        return;
    }
    int ans = 0;
    for(int i = 0, p = 0; i < t.size(); i += 2, p++) {
        if(t[i] == '0' && t[i + 1] == '0') {
            continue;
        }
        if(k > 1) {
            int m = k - 1;
            k = 1;
            if(m > p) {
                cout << -1 << "\n";
                return;
            } 
            add(ans, dp[m]);
        }
        if(t[i] == '1' && t[i + 1] == '0') {
            add(ans, (dp[p] + 1) % MOD);
        } else if(t[i] == '1' && t[i + 1] == '1') {
            add(ans, (2LL * dp[p] + 2) % MOD);
        } else if(t[i] == '0' && t[i + 1] == '1') {
            add(ans, (3LL * dp[p] + 3) % MOD);
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        dp[i] = (4LL * dp[i - 1] + 4) % MOD;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
