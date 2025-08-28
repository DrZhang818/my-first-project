#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void q1(int x) {
    cout << "swap " << x << endl;
}
int q2(int x) {
    cout << "throw " << x << endl;
    int cnt;
    cin >> cnt;
    return cnt;
}
void solve() {
    int n;
    cin >> n;
    vector<int> ans(n + 1);
    vector<int> id(n + 1);
    iota(id.begin(), id.end(), 0);
    vector<int> dp(n + 1);
    dp[n - 1] = q2(n - 1);
    ans[n - 1] = (dp[n - 1] == 1 ? 2 : 1);
    for(int i = n - 2; i >= 1; i--) {
        int c = q2(i);
        if(ans[id[i + 1]] == 1) {
            if(c == dp[i + 1] + 1) {
                ans[i] = 1;
            } else {
                ans[i] = 2;
            }
            dp[i] = c;
        } else {
            if(c != dp[i + 1] + 1) {
                ans[i] = 2;
                dp[i] = c;
                if(c != dp[i + 2] + 1) {
                    dp[i + 2] = c - 1;
                    ans[i + 2] = 2;
                }
            } else {
                if(c == dp[i + 2] + 1) {
                    ans[i] = 2;
                    dp[i] = c;
                    continue;
                }
                q1(i + 1);
                swap(id[i + 1], id[i + 2]);
                dp[i + 2] = 1;
                if(i + 4 <= n) {
                    dp[i + 2] += dp[i + 4];
                }
                dp[i + 1] = dp[i + 2] + 1;
                c = q2(i);
                if(c == dp[i + 1] + 1) {
                    ans[i] = 1;
                    dp[i] = c;
                } else {
                    ans[i] = 2;
                    dp[i] = c;
                }
            }   
        }
    }
    cout << "! ";
    for(int i = 1; i <= n; i++) {
        cout << " " << ans[i];
    }
    cout << endl;
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
