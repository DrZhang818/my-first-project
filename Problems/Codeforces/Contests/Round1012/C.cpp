#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

 
struct info {
    int d, x, y, nxt;
};  
vector<info> pre;
int sz;

void solve() { 
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int,int> vis;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }   
    int i = 0, j = 0;
    for(int p = 0; p < n; p++) {
        if(a[p] == 0) {
            while(vis[j]) j = pre[j].nxt;
            cout << pre[j].x << " " << pre[j].y << "\n";
            vis[j] = 1;
            j = pre[j].nxt;
        } else {
            while(vis[i]) i++;
            cout << pre[i].x << " " << pre[i].y << "\n";
            vis[i] = 1;
            i++;
        }
    }
    
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    pre.reserve(202884);
    for(int i = 1; i <= 318; i++) {
        int st = 3 * i - 1;
        int sx = 1, sy = 3 * (i - 1) + 1;
        for(int j = 1; j <= i; j++) {
            pre.push_back({st, sx, sy, 0});
            pre.push_back({st + 1, sx + 1, sy, 0});
            pre.push_back({st + 1, sx, sy + 1, 0});
            pre.push_back({st + 4, sx + 1, sy + 1, 0});
            sx += 3;
            sy -= 3;
        }
    }
    sort(pre.begin(), pre.end(), [&](auto p, auto q) -> bool {
        if(p.d != q.d) return p.d < q.d;
        if(p.x != q.x) return p.x < q.x;
        return p.y < q.y;
    });
    sz = pre.size();
    for(int i = sz - 1, suf = 0; i >= 0; i--) {
        if(pre[i].d % 3 == 2) {
            pre[i].nxt = suf;
            suf = i;
        }
    }
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
