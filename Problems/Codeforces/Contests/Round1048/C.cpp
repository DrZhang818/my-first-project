#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int k;
    ll x;
    cin >> k >> x;
    ll s = 1LL << k;
    vector<int> a;
    while(x != s) {
        if(x < s) {
            a.push_back(1);
        } else {
            a.push_back(2);
        }
        x = (x << 1) & ((s << 1) - 1);
    }
    reverse(a.begin(), a.end());
    cout << a.size() << "\n";
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
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
