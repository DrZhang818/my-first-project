#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    auto [x, y] = minmax_element(a.begin() + 1, a.end());
    int mn = *x, mx = *y;
    int pn = x - a.begin(), pm = y - a.begin();
    vector<PII> ans;
    if(mn + mx >= 0) {
        for(int i = 1; i <= n; i++) {
            if(i == pm) continue;
            a[i] += mx;
            ans.push_back({i, pm});
        }
        for(int i = 2; i <= n; i++) {
            if(a[i] < a[i - 1]) {
                a[i] += a[i - 1];
                ans.push_back({i, i - 1});
            }
        }
    } else {
        for(int i = 1; i <= n; i++) {
            if(i == pn) continue;
            a[i] += mn;
            ans.push_back({i, pn});
        } 
        for(int i = n - 1; i >= 1; i--) {
            if(a[i] > a[i + 1]) {
                a[i] += a[i + 1];
                ans.push_back({i, i + 1});
            }
        }
    }
    cout << (int)ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i].first << " " << ans[i].second << "\n";
    }
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
    
