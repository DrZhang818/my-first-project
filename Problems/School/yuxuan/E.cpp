#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<vector<char>> a(n + 1, vector<char>(6));
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= 5; j++) {
            cin >> a[i][j];
        }
    }
    ll ans = 0;
    vector<int> c0, c1;
    c0.push_back(0);
    c1.push_back(0);
    bool flag = false;
    int cur = 0;
    for(int i = 1; i <= n; i++) {
        bool ok = false;
        for(int j = 1; j <= 5; j++) {
            if(a[i][j] == '@') {
                ok = true;
                break;
            }
            if(a[i][j] == '.' && a[i - 1][j - 1] == '.' && a[i][j - 1] == '#' && a[i - 1][j] == '#') {
                cur++;
            }
            if(a[i][j] == '#' && a[i - 1][j - 1] == '#' && a[i][j - 1] == '.' && a[i - 1][j] == '.') {
                cur++;
            }
        }
        if(ok || i == n) {
            if(flag == true) {
                c1.push_back(cur);
            } else {
                c0.push_back(cur);
            }
            cur = 0;
            flag = !flag;
        }
    }
    int n0 = c0.size() - 1, n1 = c1.size() - 1;
    for(int i = 1; i <= n0; i++) {
        c0[i] += c0[i - 1];
    }
    for(int i = 1; i <= n1; i++) {
        c1[i] += c1[i - 1];
    }
    ans = c0[n0] + 10 * c1[n1];
    for(int i = 1; i <= n1; i++) {
        ans = min(ans, (ll)c0[i] + 10 * c1[i-1] + c1[n1] - c1[i-1] + 10 * (c0[n0] - c0[i]));
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
