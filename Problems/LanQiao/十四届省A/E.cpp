#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P9233
/*
    树上启发式合并
    题意:
        给定一颗N个节点的树, 其中1是树根, 树的每个点有一个颜色C
        定义一棵树是颜色平衡树, 当且仅当该树中每种颜色的节点个数相同
        求出这棵树中有多少个子树是颜色平衡树
        输入时按顺序给出节点1~N的颜色、父节点
        范围: N∈[1,2e5], C∈[1,2e5]
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        首先观察题目性质, 由于涉及求解所有子树, 并且以u为根的答案完全可以由
        以son[u]为根的树转移, 因此考虑自底向上的dfs(后序遍历dfs)
        接下来思考如何维护"颜色是否平衡"这个信息
        我们可以想到使用哈希表来统计每个颜色的次数, 这样判断时就只需要扫一遍哈希表就可以了
        由没有什么方法来优化判断逻辑呢?
        可以再开一个哈希表统计每种次数有多少种颜色, 这直接对应于"颜色是否平衡",
        因为"颜色平衡"等价于只有一种次数
        下面是本题最难的地方: 如何实现由子到父的转移
        我们会发现这个合并逻辑并不能做到O(1)转移, 似乎必须要暴力转移
        直觉上来说, 这样暴力做肯定是要超时的, 有没有方法来优化呢?
        我们进一步思考合并的过程, 实质上就是对两个map进行合并
        设第一个map为A, 第二个为B
        A -> B和B -> A的结果显然是一样的
        因此在合并的时候, 我们可以始终让小map向大map合并, 这样处理的次数就会小很多
        根据DSU on tree理论, 对于每个节点, 它被暴力复制的次数约为log(n)
        这样总时间复杂度就是O(nlogn)的
        需要注意的是, 本题并不是标准的基于重链剖分的树上启发式合并, 而是基于umap大小
        的启发式合并, 效果是相似的
*/
struct info {
    unordered_map<int,int> freq;
    unordered_map<int,int> freqCnt;
};
void solve() { 
    int n;
    cin >> n;
    vector<int> C(n + 1);
    vector<vector<int>> son(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> C[i];
        int fa;
        cin >> fa;
        if(fa) son[fa].push_back(i);
    }
    int ans = 0;
    function<info(int)> dfs = [&](int u) -> info {
        info ds;
        ds.freq[C[u]] = 1;
        ds.freqCnt[1] = 1;
        for(int v : son[u]) {
            info vds = dfs(v);
            if(vds.freq.size() > ds.freq.size()) swap(ds, vds);
            for(auto it = vds.freq.begin(); it != vds.freq.end(); it++) {
                int col = it->first, cnt = it->second;
                int oldCnt = 0;
                if(ds.freq.count(col)) {
                    oldCnt = ds.freq[col];
                    ds.freqCnt[oldCnt]--;
                    if(ds.freqCnt[oldCnt] == 0) {
                        ds.freqCnt.erase(oldCnt);
                    }
                }
                int newCnt = oldCnt + cnt;
                ds.freq[col] = newCnt;
                ds.freqCnt[newCnt]++;
            }
        }
        if(ds.freqCnt.size() == 1) ans++;
        return ds;
    };
    dfs(1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
