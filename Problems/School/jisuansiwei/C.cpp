#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


constexpr int inf = 1000000000;
struct info {
    int pos, len, pre, nxt;
};
void solve() { 
    int n;
    cin >> n;
    vector<info> a(n + 1);
    int mn = inf, x, cur;
    for(int i = 1; i <= n; i++) {
        cin >> a[i].pos >> a[i].len;
        a[i].pre = i == 1 ? n : i - 1;
        a[i].nxt = i == n ? 1 : i + 1;
        if(a[i].pos < mn) {
            mn = a[i].pos;
            cur = i;
        }
    }
    while(cin >> x) {
        if(x == -1) break;
        int t = cur, pos = -1, mn = inf;
        while(1) {
            if(a[cur].len >= x && a[cur].len < mn) {
                mn = a[cur].len;
                pos = cur;
            }
            cur = a[cur].nxt;
            if(cur == t) break;
        }
        if(pos == -1) continue;
        cur = pos;
        a[cur].len -= x;
        if(a[cur].len == 0) {
            a[a[cur].pre].nxt = a[cur].nxt;
            a[a[cur].nxt].pre = a[cur].pre;
            cur = a[cur].nxt;
        }
    }
    if(a[cur].len == 0) return;
    int t = cur;
    while(1) {
        cout << a[cur].pos << " " << a[cur].len << "\n";
        cur = a[cur].nxt;
        if(cur == t) break;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
