#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for(int l = 1; l <= n; l++) {
        for(int r = l; r <= n; r++) {
            int sum = 0;
            for(int i = l; i <= r; i++) {
                sum += a[i];
            }
            bool ok = true;
            for(int i = l; i <= r; i++) {
                if(sum % a[i] == 0) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                ans++;
            }
        }
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
