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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    map<int,int> mp;
    for(int i = 1; i <= n; i++) {
        int rem = a[i] % k;
        mp[min(rem, k - rem)]++;
    }
    for(int i = 1; i <= n; i++) {
        int rem = b[i] % k;
        mp[min(rem, k - rem)]--;
        if(mp[min(rem, k - rem)] == 0) {
            mp.erase(min(rem, k - rem));
        }
    }
    if(mp.size() == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
