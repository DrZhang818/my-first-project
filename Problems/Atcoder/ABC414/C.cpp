#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

ll get(int x, int tag) {
    vector<int> num;
    ll res = x;
    while(x) {
        num.push_back(x % 10);
        x /= 10;
    }
    for(int i = tag; i < num.size(); i++) {
        res = res * 10 + num[i];
    }
    return res; 
}
void solve() {
    int base;
    ll n;
    cin >> base >> n;
    auto ck = [&](ll x) -> bool {
        vector<int> num;
        while(x) {
            num.push_back(x % base);
            x /= base;
        }
        int n = num.size();
        for(int i = 0; i < n; i++) {
            if(num[i] != num[n - i - 1]) {
                return false;
            }
        }
        return true;
    };
    ll ans = 0;
    for(int i = 1; ; i++) {
        ll x = get(i, 0);
        if(x > n) break;
        if(ck(x)) ans += x;
    }
    for(int i = 1; ; i++) {
        ll x = get(i, 1);
        if(x > n) break;
        if(ck(x)) ans += x;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
