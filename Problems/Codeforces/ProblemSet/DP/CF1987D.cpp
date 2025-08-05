#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void chmin(int &x, int y) {
    if(x > y) {
        x = y;
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }    
    vector<int> a{0};
    for(int i = 1; i <= n; i++) {
        if(cnt[i]) {
            a.push_back(i);
        }
    }
    n = a.size() - 1;
    vector<int> dp(n + 1, inf);
    dp[0] = 0;
    for(int i = 0; i < n; i++) {
        vector<int> ndp(n + 1, inf);
        for(int j = 0; j <= i; j++) {
            chmin(ndp[j + 1], dp[j] + 1);
            if(j - cnt[a[i + 1]] >= 0) {
                chmin(ndp[j - cnt[a[i + 1]]], dp[j]);
            }
        }
        swap(dp, ndp);
    }
    cout << *min_element(dp.begin(), dp.end()) << "\n";
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
