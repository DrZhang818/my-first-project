#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> neg, pos;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(x < 0) {
            neg.push_back(-x);
        } else {
            pos.push_back(x);
        }
    }
    sort(neg.begin(), neg.end());
    sort(pos.begin(), pos.end());
    if(pos.empty()) swap(pos, neg);
    if(!pos.empty() && !neg.empty() && pos.back() < neg.back()) {
        swap(pos, neg);
    }
    ll ans = 0;
    for(int i = pos.size() - 1; i >= 0; i -= k) {
        ans += 2 * pos[i];
    }   
    for(int i = neg.size() - 1; i >= 0; i -= k) { 
        ans += 2 * neg[i];
    }
    ans -= pos.back();
    cout << ans << "\n";
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
