#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n;
    int q;
    cin >> n >> q;

    ll k = (1LL << __lg(n)) - 1;
    ll rem = n - k;

    while(q--) {
        ll x;
        cin >> x;
        if(x > k) {
            cout << rem << "\n";
        } else {
            cout << (1LL << __lg(x)) << "\n";
        }
    }

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
