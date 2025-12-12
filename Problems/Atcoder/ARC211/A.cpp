#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    array<int,10> a;
    ll sum = 0;
    for(int i = 1; i <= 9; i++) {
        cin >> a[i];
        if(i != 5) {
            sum += a[i];
        }
    }    
    int c = a[5];
    ll ans = 0;
    if(c > sum + 1) {
        ans = c - sum - 1;
    } else {
        int m = 0; 
        for(int i = 1; i <= 9; i++) {
            if(a[i] > 0) {
                m++;
            }
        }
        if(m == 2) {
            for(int i = 1; i <= 4; i++) {
                if(a[i] > 0 && a[10 - i] > 0) {
                    ans = 1;
                    break;
                }
            }
        }
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
