#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


//https://codeforces.com/contest/2025/problem/D
void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> dp(m + 2), d(m + 2);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] > 0) {
            if(a[i] <= sum) {
                d[a[i]]++;
                d[sum + 1]--;
            }
        } else if(a[i] < 0) {
            a[i] = -a[i];
            if(sum - a[i] >= 0) {
                d[0]++;
                d[sum - a[i] + 1]--;
            }
        } else {
            for(int i = 1; i <= sum; i++) {
                d[i] += d[i - 1];
            }
            for(int i = 0; i <= sum; i++) {
                dp[i] += d[i];
            }
            sum++;
            for(int i = sum; i >= 1; i--) {
                dp[i] = max(dp[i - 1], dp[i]);
            }
            d.assign(m + 2, 0);
        }
    }
    for(int i = 1; i <= sum; i++) {
        d[i] += d[i - 1];
    }
    for(int i = 0; i <= sum; i++) {
        dp[i] += d[i];
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
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
