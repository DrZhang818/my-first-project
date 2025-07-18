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
    vector<int> s(n + 1, -1);
    int x = 0;
    bool ok = false;
    for(int L = 1, R = 2; R <= n; R++) {
        cout << "? " << L << " " << R << endl;
        cin >> x;
        if(x == 0) {
            continue;
        }
        s[R] = 1;
        ok = true;
        for(int i = R - 1; i >= L; i--) {
            if(x > 0) {
                s[i] = 0;
                x--;
            } else {
                s[i] = 1;
            }
        }
        L = R + 1;
        R = L;
    }
    if(!ok) {
        cout << "! ";
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    int sum = 0;
    cout << "? " << 1 << " " << n << endl;
    cin >> sum;
    vector<int> dp(2);
    for(int i = 1; i <= n; i++) {
        if(s[i] == 1) {
            dp[1] += dp[0];
        } else if(s[i] == 0) {
            dp[0] += 1;
        } else {
            if(dp[1] < sum) {
                s[i] = 1;
                dp[1] += dp[0];
            } else {
                s[i] = 0;
            }
        }
    }
    cout << "! ";
    for(int i = 1; i <= n; i++) {
        cout << s[i];
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
