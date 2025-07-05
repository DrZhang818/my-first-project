#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


const int inf = 1000000000;
void solve(int id){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mx = -inf;
    int start = 1, end = 1, p = 1, sum = 0;
    for(int i = 0; i < n; i++) {
        sum += a[i];
        if(sum > mx) {
            mx = sum;
            start = p;
            end = i + 1;
        }
        if(sum < 0) {
            sum = 0;
            p = i + 2;
        }
    }
    cout << "Case " << id << ":\n";
    cout << mx << " " << start << " " << end << "\n";
}
void solve1(int id) {
    int n;
    cin >> n;
    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> dp[i];
    }
    int start = 1, end = 1, p = 1, mx = dp[1];
    for(int i = 2; i <= n; i++) {
        if(dp[i - 1] + dp[i] >= dp[i]) {
            dp[i] = dp[i - 1] + dp[i];
        } else {
            p = i;
        }
        if(dp[i] >= mx) {
            mx = dp[i];
            start = p;
            end = i;
        }
    }
    cout << "Case " << id << ":\n";
    cout << mx << " " << start << " " << end << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        solve1(i);
        cout << "\n";
    }
    return 0;
}

