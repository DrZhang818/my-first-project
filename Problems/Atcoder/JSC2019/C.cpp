#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n << 1 | 1);
    for(int i = 0, t = 0; i < 2 * n; i++) {
        int cur = s[i] == 'W' ? 0 : 1;
        if(cur == t) {
            a[i + 1] = 0;
        } else {
            a[i + 1] = 1;
            t ^= 1;
        }
    }
    vector<int> S, T;
    for(int i = 1; i <= 2 * n; i++) {
        if(i == 1) {
            S.push_back(i);
            a[i] ^= 1;
        } else if(i == 2 * n) {
            T.push_back(i);
        } else {
            if(a[i] == 1) {
                S.push_back(i);
                a[i] ^= 1;
            } else {
                T.push_back(i);
                a[i + 1] ^= 1;
            }
        }
    }
    if(S.size() != T.size()) {
        cout << 0 << "\n";
        return;
    }
    for(int i = 1; i <= 2 * n; i++) {
        if(a[i] != 0) {
            cout << 0 << "\n";
            return;
        }
    }
    int ans = 1;
    for(int i = S.size() - 1, j = T.size(), c = 0; i >= 0; i--) {
        while(j > 0 && T[j - 1] > S[i]) {
            j--;
            c++;
        }
        if(c == 0) {
            cout << 0 << "\n";
            return;
        }
        ans = 1LL * ans * c % MOD;
        c--;
    }
    for(int i = 1; i <= n; i++) {
        ans = 1LL * ans * i % MOD;
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
