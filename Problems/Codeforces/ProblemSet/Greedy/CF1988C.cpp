#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    ll n;
    cin >> n;
    vector<ll> a;
    for(int i = 62; i >= 0; i--) {
        if(n >> i & 1) {
            a.push_back(n ^ (1LL << i));
        }
    }
    if(a.size() == 1) {
        a.pop_back();
    }
    a.push_back(n);
    cout << a.size() << "\n";
    for(ll x : a) {
        cout << x << " \n"[x == a.back()];
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
