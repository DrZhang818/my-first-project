#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int count(ll x) {
    int res = 0;
    do {
        res++;
        x /= 10;
    } while(x);
    return res;
}

ll power10[18];
int init = []() {
    power10[0] = 1;
    for(int i = 1; i <= 17; i++) {
        power10[i] = power10[i - 1] * 10;
    }
    return 1;
}();

void solve() {  
    ll l, r;
    cin >> l >> r;
    if(count(l) != count(r)) {
        if(count(r - 1) != count(r)) {
            cout << r - 1 << "\n";
            return;
        } else {
            l = power10[count(r) - 1];
        }
    }

    int bit = count(r);
    ll num = 0;
    for(int i = 1; i <= bit; i++) {
        int up = r % 10;
        if(up == 9) {
            num = num * 10 + 9;
            r /= 10;
            l /= 10;
            continue;
        } 
        if(r / 10 - 1 >= l / 10) {
            num = num * 10 + 9;
            l /= 10;
            r /= 10;
            r--;
        } else {
            num = num * 10 + up;
            l /= 10;
            r /= 10;            
        }
    }

    cout << num << "\n";
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
