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
    int mx = 0;
    ll sum = 0;
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        mx = max(mx, x);
        sum += x;
    }
    sum -= mx;
    if(sum < n && mx > 0) {
        cout << "Donkey\n";
    } else {
        cout << "Puss in Boots\n";
    }
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
