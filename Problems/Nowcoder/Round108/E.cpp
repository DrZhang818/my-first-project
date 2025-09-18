#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 20000;

vector<int> num;
bool ck(int x) {
    int t = sqrt(x);
    return t * t == x || (t + 1) * (t + 1) == x;
}
int dp[101][N + 1];
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    int ans = n - 1 + dp[n][sum];
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 1; i <= N; i++) {
        int x = i, s = 0;
        while(x) {
            s += x % 10;
            x /= 10;
        }
        if(ck(i) && ck(s)) {
            num.push_back(i);
        }
    }
    
    dp[0][0] = 1;
    for(int i = 1; i <= 100; i++) {
        for(int x : num) {
            for(int j = x; j <= N; j++) {
                dp[i][j] |= dp[i - 1][j - x];
            }
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
