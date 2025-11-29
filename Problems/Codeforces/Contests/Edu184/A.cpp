#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    ll a;
    cin >> n >> a;
    vector<ll> v(n + 1);
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    int L = 0;
    while(L + 1 <= n && v[L + 1] < a) {
        L++;
    }
    int R = n + 1;
    while(R - 1 >= 1 && v[R - 1] > a) {
        R--;
    }
    if(L > n - R + 1) {
        cout << v[L] << "\n";
    } else {
        cout << (R == n + 1 ? a : v[R]) << "\n";
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
