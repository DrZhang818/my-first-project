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
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mp[x]++;
    }
    ll A = 0, B = 0;
    vector<int> val;    
    for(auto &[x, c] : mp) {
        if(x & 1) {
            val.push_back(c);
        }
        A += 1LL * x / 2 * c;
        B += 1LL * x / 2 * c;
    }
    sort(val.begin(), val.end(), greater<int>());
    for(int i = 0; i < val.size(); i++) {
        if(i % 2 == 0) {
            A += val[i];
        } else {
            B += val[i];
        }
    }
    cout << A << " " << B << "\n";
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
