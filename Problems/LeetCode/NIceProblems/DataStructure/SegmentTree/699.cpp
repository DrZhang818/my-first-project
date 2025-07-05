#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://leetcode.cn/problems/falling-squares/description/
/*
    线段树 || 离散化
    题意:
        在二维平面中, 有q次询问, 每次询问会掉落一个左边界为L, 长度为len的正方形
        你需要依次回答每次询问后方块堆叠的最大高度
        1 <= q <= 1000; 1 <= L <= 1e8; 1 <= len <= 1e6
    关键思考:
        每次询问相当于把[L, L + len]的区间最大值进行更新
        容易发现以下性质:
            更新后的最大值由更新前的最大值 + 当前方块的len得到
        因此只需要找到一种数据结构支持高效区间修改和高效区间查询即可
        线段树可以满足这一需求
        但本题的L范围过大, 而询问次数q有限
        这意味着空间中有着大量的空白位置, 可以使用离散化来节约这些用不到的空间
        离散化的方法:
            (1)收集端点
            (2)排序去重
            (3)下标映射 : 即排序去重后的数组中每个元素的下标
    代码实现:
        1.线段树的维护max版本, 支持update方法
        2.注意一个细节, 当方块1右端点和方块2左端点重合时候, 由题意二者要有所区分
          因此处理方法就是在添加右端点时候进行-1操作, 也就是写成左闭右开区间的形式
          这样就可以正确处理所有端点了
*/
class SegmentTree{
private:
    int n;
    vector<ll> mx;
    vector<ll> change;
    vector<bool> updateArr;
    void up(int i){
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }
    void down(int i){
        if(updateArr[i]){
            updateLazy(i << 1, change[i]);
            updateLazy(i << 1 | 1, change[i]);
            updateArr[i] = false;
        }
    }
    void updateLazy(int i, ll v){
        mx[i] = v;
        change[i] = v;
        updateArr[i] = true;
    }
    void updateHelp(int ul, int ur, ll v, int l, int r, int i){
        if(ul <= l && r <= ur){
            updateLazy(i, v);
        }else{
            int mid = (l + r) >> 1;
            down(i);
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
            return mx[i];
        }
        int mid = (l + r) >> 1;
        down(i);
        ll ans = LLONG_MIN;
        if(ql <= mid){
            ans = max(ans,queryHelp(ql, qr, l, mid, i << 1));
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
//力扣版本
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> ans(positions.size());
        vector<int> nums;
        for(auto &pos : positions){
            nums.push_back(pos[0]);
            nums.push_back(pos[0] + pos[1] - 1);
        }
        sort(nums.begin(), nums.end());
        nums.erase(unique(nums.begin(), nums.end()), nums.end());
        int n = nums.size();
        unordered_map<int,int> id;
        for(int i = 0; i < n; i++){
            id[nums[i]] = i;
        }
        SegmentTree st(n);
        int h = 0, mx = 0, i = 0;
        for(auto &q : positions){
            int l = id[q[0]];
            int r = id[q[0] + q[1] - 1];
            h = st.query(l, r) + q[1];
            mx = max(mx, h);
            st.update(l, r, h);
            ans[i++] = mx;
        }
        return ans;
    }

};

//CF版本

void solve(){
    int q;
    cin >> q;
    vector<PII> a(q);
    set<int> st;
    unordered_map<int, int> mp;
    for(int i = 0; i < q; i++){
        int l, len;
        cin >> l >> len;
        a[i].first = l;
        a[i].second = len;
        st.insert(l);
        st.insert(l + len - 1);
    }
    int i = 0;
    for(auto num : st){
        mp[num] = i++;
    }
    
    SegmentTree tree(st.size());
    ll mx = 0;
    for(auto &[left, len] : a){
        int l = mp[left];
        int r = mp[left + len - 1];
        ll h = tree.query(l, r);
        tree.update(l, r, h + len);
        mx = max(mx, h + len);
        cout << mx << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}