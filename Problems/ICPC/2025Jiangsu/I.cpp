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
    map<int,int> mp1,mp2,mp3;
    map<PII,int> mp12,mp23,mp13;
    map<tuple<int,int,int>, int> mp123;
    vector<array<int,3>> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        a[i] = {x, y, z};
        mp1[x]++;
        mp2[y]++;
        mp3[z]++;
        mp12[{x, y}]++;
        mp23[{y, z}]++;
        mp13[{x, z}]++;
        mp123[{x, y, z}]++;
    }    
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        auto [x, y, z] = a[i];
        ll c1 = mp1[x] - mp12[{x, y}] - mp13[{x, z}] + mp123[{x, y, z}];
        ll c2 = mp2[y] - mp12[{x, y}] - mp23[{y, z}] + mp123[{x, y, z}];
        ll c3 = mp3[z] - mp13[{x, z}] - mp23[{y, z}] + mp123[{x, y, z}];
        ll c12 = mp12[{x, y}] - mp123[{x, y, z}];
        ll c13 = mp13[{x, z}] - mp123[{x, y, z}];
        ll c23 = mp23[{y, z}] - mp123[{x, y, z}];
        ll c123 = mp123[{x, y, z}] - 1;

        ans += c1 * (c2 + c3 + c12 + c13 + c23 + c123);
        ans += c2 * (c3 + c12 + c13 + c23 + c123);
        ans += c3 * (c12 + c13 + c23 + c123);
        ans += c12 * (c12 - 1) / 2 + c12 * (c23 + c13 + c123);
        ans += c13 * (c13 - 1) / 2 + c13 * (c23 + c123);
        ans += c23 * (c23 - 1) / 2 + c23 * c123;
        ans += c123 * (c123 - 1) / 2;
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
