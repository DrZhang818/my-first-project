#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc411/tasks/abc411_d
/*
    dfs || 拓扑序
    题意:
        有一台服务器和N个主机, 服务器和主机都可以存储字符串, 起始都为空
        现在有Q次询问, 询问共分为3种, 你需要依次执行询问:
        op1: 给定p, 把第p个主机的字符串替换为服务器所存的字符串
        op2: 给定p和字符串s, 把第p个主机的字符串在结尾追加s
        op3: 给定p, 把服务器的字符串替换为第p个主机所存的字符串
        输出最终服务器所存的字符串
        范围: N∈[1,2e5], Q∈[1,2e5], p∈[1,N], ∑len(s) <= 1e6
    关键思考:
        本题为数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先考虑暴力操作, 如果模拟题意的话, 会有大量字符串拷贝的开销, 时间复杂度为O(q∑|s|)
        观察后发现, 可以把题目建模为状态机, 那么最后服务器的状态仅由前驱状态决定
        换句话说, 我们可以把操作看作有限状态机上的转移, 那么操作序列实际上构成了拓扑序 
        我们只需要关注最后一个节点为op3的链即可
        因此比较简单的解决方法为: 收集所有的操作序列后, 逆向做一次回溯即可
        利用cur表示当前要找的主机, 特别规定服务器的序号为0
        定义dfs(i,j) := 考虑前i个操作序列, 序号为j的主机的最终状态
        记x = a[i].id, op = a[i].op
        (1)如果j = 0且op = 3:
            则有dfs(i,j) = dfs(i-1,x)
        (2)如果x = j:
            若op = 1:
                则dfs(i,j) = dfs(i-1,0)
            若op = 2:
                则dfs(i,j) = dfs(i-1,j) + s
        (3)其余情况:
            dfs(i,j) = dfs(i-1,j)
*/  
struct info {
    int op, id;
    string s;
};
void solve() {
    int n, q;
    cin >> n >> q;
    vector<info> a(q + 1);
    for(int i = 1; i <= q; i++) {
        cin >> a[i].op >> a[i].id;
        if(a[i].op == 2) {
            cin >> a[i].s;
        }
    }
    auto dfs = [&](auto &&self, int i, int j) -> string {
        if(i == 0) return "";
        if(j == 0 && a[i].op == 3) return self(self, i - 1, a[i].id);
        if(a[i].id == j && a[i].op == 1) return self(self, i - 1, 0);
        if(a[i].id == j && a[i].op == 2) return self(self, i - 1, j) + a[i].s;
        return self(self, i - 1, j); 
    };
    cout << dfs(dfs, q, 0) << "\n";
}
// 递推写法
// stack<string> stk;
// int cur = 0;
// for(int i = q; i >= 1; i--) {
//     if(cur == 0 && a[i].op == 3) {
//         cur = a[i].id;
//     } else if(a[i].id == cur) {
//         if(a[i].op == 1) {
//             cur = 0;
//         } else {
//             stk.push(a[i].s);
//         }
//     }
// }
// while(!stk.empty()) {
//     cout << stk.top();
//     stk.pop();
// }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
