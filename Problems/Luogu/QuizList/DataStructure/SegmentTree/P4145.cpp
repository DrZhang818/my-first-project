#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://www.luogu.com.cn/problem/P4145
class SegmentTree{
private:
    int n;
    vector<ll> sum;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void build(vector<ll>& nums, int l, int r, int i){
        if(l == r){
            sum[i] = nums[l];
        }else{
            int mid = (l + r) >> 1;
            build(nums, l, mid, i << 1);
            build(nums, mid + 1, r, i << 1 | 1);
            up(i);
        }
    }
    void sqrtHelp(int ql, int qr, int l, int r, int i){
        if(l == r){
            sum[i] = (ll)sqrt(sum[i]);
            return;
        }
        int mid = (l + r) >> 1;
        if(ql <= mid && sum[i << 1] != mid - l + 1){
            sqrtHelp(ql, qr, l, mid, i << 1);
        }
        if(qr > mid && sum[i << 1 | 1] != r - mid){
            sqrtHelp(ql, qr, mid + 1, r, i << 1 | 1);
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
        build(nums, 0, n - 1, 1);   
    }
    void update(int ql, int qr){
        sqrtHelp(ql, qr, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    SegmentTree st(a);
    int m;
    cin >> m;
    while(m--){
        int flag, l, r;
        cin >> flag >> l >> r;
        if(l > r) swap(l, r);
        if(flag == 0){
            st.update(l - 1, r - 1);
        }
        else{
            ll ans = st.query(l - 1, r - 1);
            cout << ans << "\n";
        }
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
