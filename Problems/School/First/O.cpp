#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;



vector<ll> tr;
int n;
inline int lowbit(int o) { return o & -o; }
void add(int o, int d) {
    for(; o <= n; o += lowbit(o)) tr[o] += d;
}
int query(int o) {
    int res = 0;
    for(; o > 0; o -= lowbit(o)) {
        res += tr[o];
    }
    return res;
}
void solve() { 
    int q;
    cin >> n >> q;
    tr.assign(n + 5, 0);
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int l, r;
            cin >> l >> r;
            add(l, 1);
            add(r + 1, -1);
        } else {
            int x;
            cin >> x;
            int cnt = query(x), cur = 0;
            while(cur < cnt && a[x] >= 10) {
                int t = 0, p = a[x];
                while(p > 0) {
                    t += p % 10;
                    p /= 10;
                }
                a[x] = t;
                cur++;
            }
            add(x, -cnt);
            add(x + 1, cnt);
            cout << a[x] << "\n";
        }
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
    
