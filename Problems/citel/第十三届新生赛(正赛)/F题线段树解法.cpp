#include <bits/stdc++.h>
using namespace std;

// 结构体存储二元组信息
struct Tuple {
    int a;
    int b;
    int c;
    int orig_idx;
};

// 线段树用于区间最大值查询及更新
struct SegmentTree {
    int size;
    vector<long long> tree;
    vector<int> idx_tree;

    SegmentTree(int n){
        size = 1;
        while(size < n) size <<=1;
        tree.assign(2*size, 0LL);
        idx_tree.assign(2*size, -1);
    }

    // 更新线段树，位置 pos 更新为 val 和对应的 tuple_idx
    void update_val(int pos, long long val, int tuple_idx){
        pos += size -1;
        if(val > tree[pos]){
            tree[pos] = val;
            idx_tree[pos] = tuple_idx;
        }
        pos >>=1;
        while(pos >=1){
            if(tree[pos<<1] >= tree[(pos<<1)|1]){
                if(tree[pos] != tree[pos<<1]){
                    tree[pos] = tree[pos<<1];
                    idx_tree[pos] = idx_tree[pos<<1];
                }
            }
            else{
                if(tree[pos] != tree[(pos<<1)|1]){
                    tree[pos] = tree[(pos<<1)|1];
                    idx_tree[pos] = idx_tree[(pos<<1)|1];
                }
            }
            pos >>=1;
        }
    }

    // 查询区间 [l, r] 的最大值及其对应的索引
    pair<long long, int> query_max(int l, int r){
        l += size -1;
        r += size -1;
        pair<long long, int> res = {0, -1};
        while(l <= r){
            if(l&1){
                if(tree[l] > res.first){
                    res.first = tree[l];
                    res.second = idx_tree[l];
                }
                l++;
            }
            if(!(r&1)){
                if(tree[r] > res.first){
                    res.first = tree[r];
                    res.second = idx_tree[r];
                }
                r--;
            }
            l >>=1;
            r >>=1;
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<Tuple> tuples(n);
        vector<int> all_vals;
        for(int i=0;i<n;i++){
            cin >> tuples[i].a >> tuples[i].b >> tuples[i].c;
            tuples[i].orig_idx = i+1;
            all_vals.push_back(tuples[i].a);
            all_vals.push_back(tuples[i].b);
        }
        // 坐标压缩
        sort(all_vals.begin(), all_vals.end());
        all_vals.erase(unique(all_vals.begin(), all_vals.end()), all_vals.end());
        // 排序二元组：按 a_i 降序，若 a_i 相同则按 b_i 降序
        sort(tuples.begin(), tuples.end(), [&](const Tuple &x, const Tuple &y) -> bool{
            if(x.a != y.a) return x.a > y.a;
            return x.b > y.b;
        });
        // 映射函数
        auto get_compressed = [&](int val) -> int{
            return lower_bound(all_vals.begin(), all_vals.end(), val) - all_vals.begin() +1;
        };
        int m = all_vals.size();
        // 初始化线段树
        SegmentTree seg(m);
        // 动态规划数组
        vector<long long> dp(n, 0);
        vector<int> prev_idx(n, -1);
        long long global_max = 0;
        int last_tuple = -1;
        for(int i=0;i<n;i++){
            int a_comp = get_compressed(tuples[i].a);
            int b_comp = get_compressed(tuples[i].b);
            // 查询 [a_i, m] 区间的最大值
            pair<long long, int> q = {0, -1};
            if(a_comp <= m){
                q = seg.query_max(a_comp, m);
            }
            dp[i] = tuples[i].c;
            if(q.first >0){
                dp[i] += q.first;
                prev_idx[i] = q.second;
            }
            // 更新线段树在 b_i 的位置
            seg.update_val(b_comp, dp[i], i);
            // 更新全局最大值
            if(dp[i] > global_max){
                global_max = dp[i];
                last_tuple = i;
            }
        }
        // 回溯选中的二元组
        vector<int> selected;
        int current = last_tuple;
        while(current != -1){
            selected.push_back(tuples[current].orig_idx);
            current = prev_idx[current];
        }
        // 反转以获得正确顺序
        reverse(selected.begin(), selected.end());
        // 输出
        cout << selected.size() << " " << global_max << "\n";
        for(int i=0;i<selected.size();i++){
            cout << selected[i] << (i < selected.size()-1 ? " " : "\n");
        }
    }
}
