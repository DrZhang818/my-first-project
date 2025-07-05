#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
int n, m;
vector<vector<ll>> a;
void add(int x, int y, int k) {
    for(int i = x; i <= n; i += i & -i) {
        for(int j = y; j <= m; j += j & -j) {
            a[i][j] += k;
        }
    }
}
ll query(int x, int y) {
    ll res = 0;
    for(int i = x; i > 0; i -= i & -i) {
        for(int j = y; j > 0; j -= j & -j) {
            res += a[i][j];
        }
    }
    return res;
}
void solve() { 
    cin >> n >> m;
    a.resize(n + 5, vector<ll>(m + 5));
    int flag;
    while(cin >> flag) {
        if(flag == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            add(x, y, k);
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            ll ans = query(c, d) - query(c, b - 1) - query(a - 1, d) + query(a - 1, b - 1);
            cout << ans << "\n";            
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
