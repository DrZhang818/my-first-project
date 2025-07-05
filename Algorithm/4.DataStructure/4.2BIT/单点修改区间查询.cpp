#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


vector<ll> bit;
int n;
void add(int i, int x) {
    for(i; i <= n; i += (i & -i)) bit[i] += x;  
}
ll query(int i) {
    ll res = 0;
    for(i; i > 0; i -= (i & -i)) res += bit[i];
    return res;
}
void solve() { 
    int q;
    cin >> n >> q;
    bit.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        add(i, x);
    }
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int i, x;
            cin >> i >> x;
            add(i, x);  
        } else {
            int l, r;
            cin >> l >> r;
            ll ans = query(r) - query(l - 1);
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
    
