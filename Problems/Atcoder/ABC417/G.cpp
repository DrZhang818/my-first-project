#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18 + 9;

//https://atcoder.jp/contests/abc417/tasks/abc417_g
/*
    数据结构 || 树链剖分 || 倍增
    题意:
        定义字符串S0 = "0", S1 = "1"
        你需要按顺序处理Q个查询
        在第i个查询中, 你会得到一个由三个整数(Li,Ri,Xi)组成的三元组
        将S[Li]和S[Ri]按顺序拼接得到字符串S[i+1], 然后输出S[i+1]的第Xi个字符
        范围: Q∈[1,5e5], Xi∈[1,1e18], Xi不超过S[i+1]的长度
    关键思考:
        本题为数据结构类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先观察题目性质, 容易发现对于每个字符串S[i], 形成的都是一个二叉树结构
        S[i]由S[l]和S[r]组成, S[l]和S[r]再递归地进行构建
        我们要查S[i]的第X个字符, 因此需要维护S[l]和S[r]的长度, 然后根据X与S[l]的长度判断去递归
        左子树查还是右子树查
        这样的问题在于, 树的高度最坏是i-1, 这样O(i)查询, 总时间复杂度就是O(Q^2)的, 无法接受
        此时, 我们可以用经典的树链剖分 + 倍增处理重链 + 暴力跳轻链的方式进行优化
        我们可以选取S[l]和S[r]中长度较大的一个作为重儿子
        最终S[i]这棵树就变成了一根重链, 我们在这个重链上进行倍增
        sum[i][s] := 以i为根的子树, 沿着重链跳2^s步跳过的字符数量
        如果我们的重儿子是左儿子, 那么沿着重链跳不会跳过字符, 因此sum[i][0] = 0
        如果我们的重儿子是右儿子, 那么沿着重链跳就会跳过左树的字符, 因此sum[i][0] = len[l[i]]
        注意, 由于sum[i][s]可能很大导致溢出, 因此我们需要与1e18取min
        查询时, 我们需要在重链上进行二分, 找到我们能到达的最低点p
        点p满足: 路径上跳过的字符数 < X, 且len(S[p]) >= X - 路径上跳过的字符数
        注意: 我们要满足路径上跳过的字符严格小于X, 这样就保证了最终一定没有到达目标, 而不是可能到达
        可能没到达, 这样就方便我们统一处理最后的 步长为1 的情况
        同时, 点p不能是0或1, 这都是为了统一处理
        最后一步决策我们手动判断 X 与len(S[l])的关系, 然后决定前往左子树 or 右子树
*/
void solve() {
    int q;
    cin >> q;
    vector<int> lson(q + 2), rson(q + 2);
    vector<ll> sz(q + 2);
    vector<array<ll,21>> sum(q + 2), son(q + 2);
    sz[0] = sz[1] = 1;
    for(int i = 2; i <= q + 1; i++) {
        int L, R;
        ll X;
        cin >> L >> R >> X;
        sz[i] = min(sz[L] + sz[R], inf);
        lson[i] = L;
        rson[i] = R;
        if(sz[L] <= sz[R]) {
            son[i][0] = L;
        } else {
            son[i][0] = R;
            sum[i][0] = sz[L];
        }
        for(int s = 1; s <= 20; s++) {
            son[i][s] = son[son[i][s - 1]][s - 1];
            sum[i][s] = min(sum[i][s - 1] + sum[son[i][s - 1]][s - 1], inf);
        }
        int cur = i;
        while(cur > 1) {
            for(int s = 20; s >= 0; s--) {
                if(son[cur][s] > 1 && sum[cur][s] < X && sz[son[cur][s]] >= X - sum[cur][s]) {
                    X -= sum[cur][s];
                    cur = son[cur][s];
                }
            }
            if(X <= sz[lson[cur]]) {
                cur = lson[cur];
            } else {
                X -= sz[lson[cur]];
                cur = rson[cur];
            }
        }
        cout << cur << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
