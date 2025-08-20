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
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    bitset<20005> dp;
    dp.set(sum);
    for(int i = 1; i <= n; i++) {
        dp = dp << a[i] | dp >> a[i];
    }  
    int d = -1;
    for(int i = sum; ; i++) {
        if(dp[i]) {
            d = i - sum;
            break;
        }
    }
    cout << (sum - d) / 2 << " " << (sum - d) / 2 + d << "\n";
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
