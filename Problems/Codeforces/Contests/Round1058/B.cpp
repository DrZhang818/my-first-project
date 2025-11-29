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
    vector<int> a(n + 1);
    int cur = 1;
    for(ll i = 1, pre = 0; i <= n; i++) {
        ll x;
        cin >> x;
        ll j = i + pre - x;
        if(j == 0) {
            a[i] = cur++;
        } else {
            a[i] = a[j];
        }
        pre = x;
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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
