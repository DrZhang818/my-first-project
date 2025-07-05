#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<db> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }   
    vector<db> ans(n + 1);
    db l = 0, r = 1.0;
    for(int i = 0; i < 60; i++) {
        db p = (l + r) / 2;
        db m = p / ((1 - p) * a[1]);
        db cur = 0;
        for(int i = 1; i <= n; i++) {
            ans[i] = a[i] * m / (1 + a[i] * m);
            cur += ans[i];
        }
        if(cur > k) r = p;
        else l = p;
    }
    for(int i = 1; i <= n; i++) {
        cout << fixed << setprecision(12) << ans[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
