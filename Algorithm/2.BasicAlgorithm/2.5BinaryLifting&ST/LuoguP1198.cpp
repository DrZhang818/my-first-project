#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class SegmentTree{
private:
    int n;
    vector<ll> mx;
    void up(int i){
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }
    void addHelp(int al, int ar, ll v, int l, int r, int i){
        if(l == r){
            mx[i] = v;
        }else{
            int mid = (l + r) >> 1;
            if(al <= mid){
                addHelp(al, ar, v, l, mid, i << 1);
            }
            if(ar > mid){
                addHelp(al, ar, v, mid + 1, r, i << 1 | 1);
            }
            up(i);
        }
    }
    ll queryHelp(int ql, int qr, int l, int r, int i){
        if(ql <= l && qr >= r){
            return mx[i];
        }
        int mid = (l + r) >> 1;
        ll ans = LLONG_MIN;
        if(ql <= mid){
            ans = max(ans, queryHelp(ql, qr, l, mid, i << 1));
        }
        if(qr > mid){
            ans = max(ans, queryHelp(ql, qr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
public:
    SegmentTree(int x){
        n = x;
        mx.resize(n << 2, 0);
    }
    void add(int l, int r, ll v){
        addHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve() { 
    int q, MOD;
    cin >> q >> MOD;
    SegmentTree tree(200005);
    ll t = 0;
    int idx = 0;
    while(q--) {
        char c;
        cin >> c;
        if(c == 'A') {
            ll n;
            cin >> n;
            n = ((n + t) % MOD + MOD) % MOD;
            tree.add(idx, idx, n);
            idx++;
        } 
        else {
            int L;
            cin >> L;
            ll ans = tree.query(idx - L, idx - 1);
            cout << ans << "\n";
            t = ans;
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
    
