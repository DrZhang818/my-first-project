#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class SegmentTree{
private:
    int n;
    vector<ll> sum;
    vector<ll> addArr;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void down(int i, int ln, int rn){
        if(addArr[i] != 0){
            addLazy(i << 1, addArr[i], ln);
            addLazy(i << 1 | 1, addArr[i], rn);
            addArr[i] = 0;
        }
    }
    void addLazy(int i, ll v, int n){
        sum[i] += v * n;
        addArr[i] += v;
    }
    void addHelp(int al, int ar, ll v, int l, int r, int i){
        if(al <= l && r <= ar){
            addLazy(i, v, r - l + 1);
        }else{
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
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
        down(i, mid - l + 1, r - mid);
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
    SegmentTree(int x){
        n = x;
        sum.resize(n << 2, 0);
        addArr.resize(n << 2, 0);
    }
    void add(int l, int r, ll v){
        addHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
    void clear() {
        for(int i = 0; i < n << 2; i++) {
            sum[i] = 0;
            addArr[i] = 0;
        }
    }
};

void solve(){
    ll n;
    cin >> n;
    vector<ll> a(n);
    SegmentTree tree(n * 2);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> s(n + 1);
    auto check = [&](ll x) -> bool {
        tree.clear();
        s.clear();
        for(int i = 0; i < n; i++) {
            s[i + 1] = s[i] + (a[i] >= x ? 1 : -1);
        }
        ll cnt = 0;
        tree.add(n, n, 1);
        for(int i = 1; i <= n; i++) {
            cnt += tree.query(0LL, s[i] + n);
            tree.add(s[i] + n, s[i] + n, 1);
        }
        return cnt >= (n * (n + 1) / 2 + 1) / 2;
    };
    vector<ll> b = a;
    sort(b.begin(), b.end());
    int l = -1, r = n;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(check(b[mid])) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << b[l] << "\n";

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

