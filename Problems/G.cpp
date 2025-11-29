#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const ull P = 13131;
const int N = 60005;
ull powp[N + 1];

void solve() {
    int n, q, m, k;
    cin >> n >> q >> m >> k;
    vector<vector<ull>> Hash(n + 1, vector<ull>(m + 1));
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        s = "#" + s;
        for(int j = 1; j <= m; j++) {
            Hash[i][j] = Hash[i][j - 1] * P + s[j];
        }
    }

    while(q--) {
        string t;
        cin >> t;
        t = "#" + t;

        vector<ull> Hash_t(m + 1);
        for(int i = 1; i <= m; i++) {
            Hash_t[i] = Hash_t[i - 1] * P + t[i];
        }

        int ans = 0;

        for(int i = 1; i <= n; i++) {
            int st = 1, cnt = 0;
            while(st <= m && cnt <= k) {
                int l = st - 1, r = m + 1;
                while(l + 1 < r) {
                    int mid = l + r >> 1;
                    if(Hash_t[mid] - Hash_t[st - 1] * powp[mid - st + 1] != Hash[i][mid] - Hash[i][st - 1] * powp[mid - st + 1]) {
                        r = mid;
                    } else {
                        l = mid;
                    }
                }
                if(r <= m) {
                    cnt++;
                }
                st = r + 1;
            }
            if(cnt <= k) {
                ans++;
            }
        }

        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    powp[0] = 1;
    for(int i = 1; i <= N; i++) {
        powp[i] = powp[i - 1] * P;
    }

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
