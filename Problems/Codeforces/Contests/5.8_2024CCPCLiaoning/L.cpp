#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    ll k;
    cin >> k;
    ull l = 2024, r = 1320000000000002024LL;
    ll t = 0;
    for(int i = 0; i <= 9; i++) {
        ll pow_100 = 1;
        for(int j = 0; j < i; j++) {
            pow_100 *= 100;
        }
        t += 2024 / (4LL * pow_100);
        if(i != 9) t -= 2024 / (100LL * pow_100);
    }
    while(l + 1 < r) {
        ull mid = l + (r - l) / 2;
        ull cur = 0;
        for(int i = 0; i <= 9; i++) {
            ll pow_100 = 1;
            for(int j = 0; j < i; j++) {
                pow_100 *= 100;
            }
            cur += mid / (4 * pow_100);
            if(i != 9) cur -= mid / (100 * pow_100);
        }
        if(mid - 2024 - cur + t >= k) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
