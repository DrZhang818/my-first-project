#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


class SegmentTree{
private:
    int n;
    vector<ll> sum;
    vector<ll> mx;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }
    void build(vector<ll>& nums, int l, int r, int i){
        if(l == r){
            sum[i] = nums[l];
            mx[i] = nums[l];
        }else{
            int mid = (l + r) >> 1;
            build(nums, l, mid, i << 1);
            build(nums, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void updateHelp(int q, ll v, int l, int r, int i){
        if(l == r){
            sum[i] = v;
            mx[i] = v;
            return;
        }
        int mid = (l + r) >> 1;
        if(q <= mid){
            updateHelp(q, v, l, mid, i << 1);
        }
        else {
            updateHelp(q, v, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
    void modHelp(int ul, int ur, ll v, int l, int r, int i){
        if(l == r){
            sum[i] %= v;
            mx[i] %= v;
            return;
        }
        int mid = (l + r) >> 1;
        if(ul <= mid && mx[i << 1] >= v){
            modHelp(ul, ur, v, l, mid, i << 1);
        }

        if(ur > mid && mx[i << 1 | 1] >= v){
            modHelp(ul, ur, v, mid + 1, r, i << 1 | 1);            
        }
        up(i);
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
    SegmentTree(vector<ll> &nums){
        n = nums.size();
        sum.resize(n << 2, 0);
        mx.resize(n << 2, 0);
        build(nums, 0, n - 1, 1);   
    }
    void update(int k, ll v){
        updateHelp(k, v, 0, n - 1, 1);
    }
    void mod(int l, int r, ll v){
        modHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }    
    SegmentTree st(a);
    while(m--){
        int flag;
        cin >> flag;
        if(flag == 1){
            int l, r;
            cin >> l >> r;
            ll ans = st.query(l - 1, r - 1);
            cout << ans << "\n";
        }
        else if(flag == 2){
            int l, r;
            ll x;
            cin >> l >> r >> x;
            st.mod(l - 1, r - 1, x);
        }
        else {
            int k;
            ll x;
            cin >> k >> x;
            st.update(k - 1, x);
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