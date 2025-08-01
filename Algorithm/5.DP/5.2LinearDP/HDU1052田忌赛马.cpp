#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://acm.hdu.edu.cn/showproblem.php?pid=1052
int cal(int x, int y) {
    if(x > y) return 200;
    if(x < y) return -200;
    return 0;
}
int n;
void solve() {
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    sort(a.begin() + 1, a.end(), greater<int>());
    sort(b.begin() + 1, b.end(), greater<int>());
    vector dp(n + 1, vector<int>(n + 1));
    for(int k = 1; k <= n; k++) {
        int x = b[n - k + 1];
        for(int i = 1; i + k - 1 <= n; i++) {
            int j = i + k - 1;
            if(i == j) {
                dp[i][j] = cal(a[i], x);
            } else {
                dp[i][j] = max(dp[i + 1][j] + cal(a[i], x), dp[i][j - 1] + cal(a[j], x));
            } 
        }
    }
    cout << dp[1][n] << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    while(cin >> n) {
        if(n == 0) break;
        solve();
    }
    return 0;
}
