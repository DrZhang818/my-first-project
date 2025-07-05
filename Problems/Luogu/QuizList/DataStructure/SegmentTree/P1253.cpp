#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://www.luogu.com.cn/problem/P1253
/*
    线段树
    题意:
        给定一个长度为n的数组, 要求编写一种数据结构, 支持一下三种操作
        op1: 给定区间[l,r], 将每个数都修改为x
        op2: 给定区间[l,r], 将每个数都加上x
        op3: 给定区间[l,r], 查询区间最大值
    关键思考:
        题目要求一种数据结构支持高效的区间修改和区间查询, 显然查询最大值这件事可以由左右儿子的信息
        在O(1)的时间内得到, 因此线段树可以完成这个任务
        只需要在sum版本的线段树中, 把up方法和lazy标记修改一下, 以及query方法变成查找max即可
*/
class SegmentTree{
private:
    int n;
    vector<ll> mx;
    vector<ll> addArr;
    vector<ll> change;
    vector<bool> updateArr;
    void up(int i){
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);        
    }
    void down(int i, int ln, int rn){
        if(updateArr[i]){
            updateLazy(i << 1, change[i], ln);
            updateLazy(i << 1 | 1, change[i], rn);
            updateArr[i] = false;
        }
        if(addArr[i] != 0){
            addLazy(i << 1, addArr[i], ln);
            addLazy(i << 1 | 1, addArr[i], rn);
            addArr[i] = 0;
        }
    }
    void updateLazy(int i, ll v, int n){
        mx[i] = v;
        addArr[i] = 0;
        change[i] = v;
        updateArr[i] = true;
    }
    void addLazy(int i, ll v, int n){
        mx[i] += v;
        addArr[i] += v;
    }
    void build(vector<ll>& nums, int l, int r, int i){
        if(l == r){
            mx[i] = nums[l];
        }else{
            int mid = (l + r) >> 1;
            build(nums, l, mid, i << 1);
            build(nums, mid + 1, r, i << 1 | 1);
            up(i);
        }
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
        if(ql <= l && r <= qr){
            return mx[i];
        }
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
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
    SegmentTree(vector<ll> &nums){
        n = nums.size();
        mx.resize(n << 2, 0);
        addArr.resize(n << 2, 0);
        change.resize(n << 2, 0);
        updateArr.resize(n << 2, false);
        build(nums, 0, n - 1, 1);   
    }
    void update(int l, int r, ll v){
        updateHelp(l, r, v, 0, n - 1, 1);
    }
    void add(int l, int r, ll v){
        addHelp(l, r, v, 0, n - 1, 1);
    }
    ll query(int ql, int qr){
        return queryHelp(ql, qr, 0, n - 1, 1);
    }
};
void solve(){
    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    SegmentTree st(a);
    while(q--){
        int flag;
        cin >> flag;
        if(flag == 1){
            ll l, r, x;
            cin >> l >> r >> x;
            st.update(l - 1, r - 1, x);           
        }
        else if(flag == 2){
            ll l, r, x;
            cin >> l >> r >> x;
            st.add(l - 1, r - 1, x);
        }
        else if(flag == 3){
            int l, r;
            cin >> l >> r;
            cout << st.query(l - 1, r - 1) << "\n";
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