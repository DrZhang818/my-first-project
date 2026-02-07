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
    ll suma = 0, sumb = 0;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        suma += a[i];
    }
    vector<ll> c(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> c[i];
        sumb += c[i];
    }
    if(suma < sumb) {
        cout << -1 << "\n";
        return;
    }
    int ans = 0;
    ll need = 0;
    for(int i = 1; i <= n; i++) {
        a[i] -= c[i];
        if(a[i] < 0) {
            need -= a[i];
            ans++;
        }
    }
    sort(a.begin() + 1, a.end(), greater());
    for(int i = 1; i <= n; i++) {
        if(need > 0) {
            ans++;
            need -= a[i];
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
