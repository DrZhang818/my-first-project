#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    vector<int> val;
    ll ans = 0;
    int cnt = 0;
    for(auto [x, c] : mp) {
        ans += 1LL * x * (c / 2 * 2);
        cnt += c / 2 * 2;
        if(c % 2 == 1) {
            val.push_back(x);
        }
    }
    sort(val.begin(), val.end(), greater<int>());
    if(val.size() == 1) {
        if(ans > val[0]) {
            ans += val[0];
            cnt++;
        }
    } else if(val.size() >= 2) {
        ll tmp1 = ans, cnt1 = cnt;
        for(int i = 0; i < val.size(); i++) {
            if(tmp1 > val[i]) {
                tmp1 += val[i];
                cnt1 += cnt;
                break;
            }
        }
        ll tmp2 = ans, cnt2 = cnt;
        for(int i = 0; i < val.size() - 1; i++) {
            int x = val[i], y = val[i + 1];
            if(ans + y > x) {
                tmp2 += x + y;
                cnt2 += 2;
                break;
            }
        }
        if(tmp2 >= tmp1) {
            ans = tmp2;
            cnt = cnt2;
        } else {
            ans = tmp1;
            cnt = cnt1;
        }
    }
    if(cnt < 3) {
        cout << 0 << "\n";
        return;
    }
    cout << ans << "\n";
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
