#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    string s;
    int q;
    cin >> n >> s >> q;
    vector<int> cm(n + 1);
    s = "#" + s;
    for(int i = 1; i <= n; i++) {
        cm[i] = cm[i - 1] + (s[i] == 'M');
    }
    auto cal = [&](int k) -> ll {
        ll dp0 = 0, dp1 = 0;
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            if(i > k) {
                int j = i - k;
                if(s[j] == 'D') {
                    int c = cm[i - 1] - cm[j];
                    dp1 -= c;
                    dp0 -= 1;
                }
            }
            if(s[i] == 'D') {
                dp0++;
            } else if(s[i] == 'M') {
                dp1 += dp0;
            } else if(s[i] == 'C') {
                ans += dp1;
            }
        }
        return ans;
    };
    while(q--) {
        int k;
        cin >> k;
        cout << cal(k) << "\n";
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
