#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class BIT{
private:
    vector<ll> a, b;
    int n;
public:
    BIT(int x) {
        a.resize(x + 1);
        b.resize(x + 1);
        n = x;
    }
    void add(int x, ll d) {
        for(int i = x; i <= n; i += i & -i) {
            a[i] += d;
            b[i] += (x - 1) * d;
        }
    }
    ll query(int x) {
        ll res = 0;
        for(int i = x; i > 0; i -= i & -i) {
            res += x * a[i] - b[i];
        }
        return res;
    }
};    
void solve() { 
    int n, m;
    cin >> n >> m;
    BIT a(n);
    for(ll i = 1, pre = 0; i <= n; i++) {
        ll x;
        cin >> x;
        a.add(i, x - pre);
        pre = x;
    }
    while(m--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            a.add(l, x), a.add(r + 1, -x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << a.query(r) - a.query(l - 1) << "\n";
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
    
