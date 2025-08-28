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
    vector<ll> ans;
    ll cur = 10;
    for(int i = 1; i <= 18; i++) {
        if(n % (cur + 1) == 0) {
            ans.push_back(n / (cur + 1));
        }
        cur *= 10;
    }
    cout << ans.size() << "\n";
    for(int i = ans.size() - 1; i >= 0; i--) {
        cout << ans[i] << " \n"[i == 0];
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
