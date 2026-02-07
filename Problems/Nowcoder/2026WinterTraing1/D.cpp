#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> mx(n + 1);
    for(int i = 1; i <= n; i++) {
        mx[i] = max(mx[i - 1], i + a[i]);
    }

    auto ck = [&](int x) -> bool {
        if(x == 0) {
            return n - count(a.begin() + 1, a.end(), 0) <= k;
        }

        int need = 0;
        int R = 0, nR = 0;
        for(int i = 1, rem = 0; i <= n; i++) {
            if(a[i] == 0) continue;

            if(i <= R) {
                nR = max(nR, i + a[i]);
            } else {
                if(rem <= 1 || i > nR) {
                    need++;
                    rem = x;
                    R = mx[i];
                    nR = 0;
                } else {
                    rem--;
                    R = nR;
                    nR = i + a[i];
                }
            }
        }
        return need <= k;
    };

    int l = -1, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    
    if(r == n + 1) {
        cout << -1 << "\n";
        return;
    }
    cout << r << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
