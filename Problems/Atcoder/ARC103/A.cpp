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
    vector<int> odd(100005), even(100005);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        if(i & 1) {
            odd[x] += 1;
        } else {
            even[x] += 1;
        }
    }
    vector<int> c1(100005), c2(100005);
    iota(c1.begin(), c1.end(), 0);
    iota(c2.begin(), c2.end(), 0);
    sort(c1.begin() + 1, c1.end(), [&](auto a, auto b){
        return odd[a] > odd[b];
    });
    sort(c2.begin() + 1, c2.end(), [&](auto a, auto b){
        return even[a] > even[b];
    });
    int ans = n;
    if(c1[1] != c2[1]) {
        ans -= odd[c1[1]];
        ans -= even[c2[1]];
    } else {
        ans -= max(odd[c1[1]] + even[c2[2]], odd[c1[2]] + even[c2[1]]);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
