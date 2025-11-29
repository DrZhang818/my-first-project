#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 200;
int dp[16][N + 1];
int pre[16][N + 1];

void solve() {
    int a, b, n, p;
    cin >> a >> b >> n >> p;
    auto work = [&](int x, int a) -> void {
        assert(dp[x][a]);
        while(x) {
            if(pre[x][a] == 1) {
                cout << 1;
                if(x != 1) cout << "//";
            } else {
                cout << 1 << pre[x][a] - 1;
            }
            a -= pre[x][a];
            x--;
        }
        assert(x == 0 && a == 0);
    };
    if(n >= 6) {
        int used = 21 - n;
        for(int x = 0; x <= used; x++) {
            int y = used - x;
            if(dp[x][a] && dp[y][b]) {
                if(a) {
                    work(x, a);
                }
                cout << "/";
                if(b) {
                    work(y, b);
                }
                if(p == 0) cout << "/";
                cout << "\n";
                return;
            }
        }
        cout << "NA\n";
        return;
    }

    int used = 6 - n;
    for(int s = 0; s < 1 << used; s++) {
        if(n == 0 && (s >> 5 & 1) != p) continue;  
        int ta = a, tb = b;
        vector<int> v;
        for(int i = 0; i < used; i++) {
            if(~s >> i & 1) {
                ta -= i + 2;
                v.push_back(0);
            } else {
                tb -= i + 2;
                v.push_back(1);
            }
        }
        if(ta < 0 || tb < 0) continue;
        for(int x = 0; x <= 15; x++) {
            int y = 15 - x;
            int cur = 0;
            if(dp[x][ta] && dp[y][tb]) {
                if(ta) {
                    work(x, ta);
                }
                cout << "/";
                cur ^= 1;
                if(tb) {
                    work(y, tb);
                }
                for(int i = 0; i < used; i++) {
                    if(cur != v[i]) {
                        cur ^= 1;
                        cout << "/";
                    }
                    cout << i + 2;
                }
                if(cur != p) cout << "/";
                cout << "\n";
                return;
            }
        }
    }
    cout << "NA\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    dp[0][0] = 1;
    for(int i = 1; i <= 15; i++) {
        for(int s = 0; s <= N; s++) {
            for(int j = 1; j <= 8; j++) {
                if(j == 2 || s + j > N) continue;
                if(dp[i][s + j] || dp[i - 1][s] == 0) continue;
                dp[i][s + j] |= dp[i - 1][s];
                pre[i][s + j] = j;
            }
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
