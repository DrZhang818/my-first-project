#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(6);
    for(int i = 1; i <= 5; i++) {
        cin >> a[i];
    }
    ll mn = *min_element(a.begin() + 1, a.end());
    cout << 4 + (n + mn - 1) / mn << "\n";
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
