#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int x1, x2, y1, y2;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    map<PII,int> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
    }
    sort(a.begin() + 1, a.end(), [&](auto x, auto y) -> bool {
        return x.x1 < y.x1;
    }); 
    for(int i = 1; i <= n; i++) {
        mp[{a[i].x2, a[i].y2}] = i;
    }
    vector<int> cnt(n + 1, 1), fa(n + 1);
    iota(fa.begin(), fa.end(), 0);
    for(int i = 1; i <= n; i++) {
        if(mp[{a[i].x1, a[i].y1}]) {
            int u = mp[{a[i].x1, a[i].y1}];
            fa[i] = fa[u];
            cnt[fa[i]]++;
        } 
    }
    int ans = 0, x, y;
    for(int i = 1; i <= n; i++) {
        if(cnt[i] > ans) {
            ans = cnt[i];
            x = a[i].x1;
            y = a[i].y1;
        }
    }
    cout << ans << " " << x << " " << y << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
