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
    vector<ll> p(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    int x, a, y, b;
    cin >> x >> a >> y >> b;
    ll k;
    cin >> k;
    sort(p.begin() + 1, p.end(), greater());
    vector<int> tag(n + 1);
    vector<int> pre1(n + 1), pre2(n + 1), pre3(n + 1);
    for(int i = 1; i <= n; i++) {
        if(i % a == 0) tag[i] = 1;
        if(i % b == 0) tag[i] = 2;
        if(i % a == 0 && i % b == 0) tag[i] = 3;
        pre1[i] = pre1[i - 1] + (tag[i] == 1);
        pre2[i] = pre2[i - 1] + (tag[i] == 2);
        pre3[i] = pre3[i - 1] + (tag[i] == 3);
    }
    auto ck = [&](int pos) -> bool {
        int c1 = pre1[pos], c2 = pre2[pos], c3 = pre3[pos];
        ll cur = 0;
        for(int i = 1; i <= n; i++) {
            if(c3) cur += p[i] / 100 * (x + y), c3--;
            else if(x > y) {
                if(c1) cur += p[i] / 100 * x, c1--;
                else if(c2) cur += p[i] / 100 * y, c2--;
                else break;
            } else {
                if(c2) cur += p[i] / 100 * y, c2--;
                else if(c1) cur += p[i] / 100 * x, c1--;
                else break;
            }
        }
        return cur >= k;
    };
    int l = 0, r = n + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << (r == n + 1 ? -1 : r) << "\n";
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
