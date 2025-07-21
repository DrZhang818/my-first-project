#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int x, y;
    ll h;
};
void solve() {
    int n;
    cin >> n;
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].h;
    }
    for(int i = 0; i <= 100; i++) {
        for(int j = 0; j <= 100; j++) {
            bool ok = true;
            bool tag = 0;
            ll H = -1;
            for(int k = 1; k <= n; k++) {
                auto [x, y, h] = a[k];
                ll res = h + abs(x - i) + abs(y - j);
                if(h > 0) {
                    if(H == -1) H = res;
                    else if(H != res) {
                        if(tag || H < res) {
                            ok = false;
                            break;
                        } else {
                            H = res;
                        }
                    }
                    tag = 1;
                } else {
                    if(H == -1) H = res;
                    else if(H != res) {
                        if(H > res && tag) {
                            ok = false;
                            break;
                        } else {
                            H = min(H, res);
                        }
                    }
                }
            }
            if(ok) {
                cout << i << " " << j << " " << H << "\n";
                return ;
            }
        }
    }
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
