#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class SegmentTree{
private:
    int n;
    ll limit;
    vector<ll> sum;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }

    void addHelp(int al, int ar, ll v, int l, int r, int i){
        if(l == r){
            sum[i] = min(sum[i] + v, limit);
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
            return sum[i];
        }
        int mid = (l + r) >> 1;
        ll ans = 0;
        if(ql <= mid){
            ans += queryHelp(ql, qr, l, mid, i << 1);
        }
        if(qr > mid){
            ans += queryHelp(ql, qr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
public:
    SegmentTree(int x, ll v){
        n = x;
        limit = v;
        sum.resize(n << 2, 0);
    }
    void add(int l, int r, ll v){
        addHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve(){
    int n, k, a, b, q;
    cin >> n >> k >> a >> b >> q;
    SegmentTree stmx(n, a), stmn(n, b);
    while(q--) {
        int flag;
        cin >> flag;
        if(flag == 1) {
            int d, v;
            cin >> d >> v;
            d -= 1;
            stmn.add(d, d, v);
            stmx.add(d, d, v);
        }
        else if(flag == 2) {
            int d;
            cin >> d;
            d -= 1;
            int ans = 0;
            if(d - 1 >= 0) ans += stmn.query(0, d - 1);
            if(d + k <= n - 1) ans += stmx.query(d + k, n - 1);
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

