#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://acm.hdu.edu.cn/showproblem.php?pid=4614
class SegmentTree{
private:
    int n;
    vector<ll> sum;
    vector<ll> change;
    vector<bool> updateArr;
    void up(int i){
        sum[i] = sum[i << 1] + sum[i << 1 | 1];
    }
    void down(int i, int ln, int rn){
        if(updateArr[i]){
            updateLazy(i << 1, change[i], ln);
            updateLazy(i << 1 | 1, change[i], rn);
            updateArr[i] = false;
        }
    }
    void updateLazy(int i, ll v, int n){
        sum[i] = v * n;
        change[i] = v;
        updateArr[i] = true;
    }
    void updateHelp(int ul, int ur, ll v, int l, int r, int i){
        if(ul <= l && r <= ur){
            updateLazy(i, v, r - l + 1);
        }else{
            int mid = (l + r) >> 1;
            down(i, mid - l + 1, r - mid);
            if(ul <= mid){
                updateHelp(ul, ur, v, l, mid, i << 1);
            }
            if(ur > mid){
                updateHelp(ul, ur, v, mid + 1, r, i << 1 | 1);
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
        change.resize(n << 2, 0);
        updateArr.resize(n << 2, false);
    }
    void update(int l, int r, ll v){
        updateHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};

void solve(){
    int n, m;
    cin >> n >> m;
    SegmentTree st(n);
    while(m--){
        int flag;
        cin >> flag;
        if(flag == 1){
            int left, cnt;
            cin >> left >> cnt;
            int sum = st.query(left, n - 1);
            if(sum == n - left){
                cout << "Can not put any one.\n";
                continue;
            }
            auto find = [&](int k) -> int{
                int l = left - 1, r = n;
                while(l + 1 < r){
                    int mid = l + (r - l) / 2;
                    if(mid - left + 1 - st.query(left, mid) >= k){
                        r = mid;
                    }else{
                        l = mid;
                    }
                }
                return r;
            };
            int l = find(1);
            int r = find(min(n - left - sum, cnt));
            cout << l << " " << r << "\n";
            st.update(l, r, 1);
        }
        else if(flag == 2){
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << "\n";
            st.update(l, r, 0);
        }
    }
}   

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
        cout << "\n";
    }
    return 0;
}
