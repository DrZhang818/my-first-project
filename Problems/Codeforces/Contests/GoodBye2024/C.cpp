#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2053/problem/C
/*
    思维 || 位运算 || 模拟决策树
    题意:
        给定两个整数n和k, 你需要对1~n的顺序排列进行下列递归操作
        let m = (l + r) // 2
        op1: 当前区间长度为偶数, 答案为F(l,r) = F(l,m) + F(m+1,r)
        op2: 当前区间长度为奇数, 答案为F(l,r) = m + F(l,m-1) + F(m+1,r)
        当 r-l+1 < k时, 停止操作
        题目要求计算出递归后得到的答案
    关键思考:
        本质上, 我们是在计算一颗完全二叉树上的奇数区间节点的权值, 节点权值定义为(l+r)//2
        对于这样一棵树, 例如[1...7]这个区间会有左子树[1...3]和右子树[5...7]
        那么两段节点的平均权重和恰为(1+7)//2 == 4
        一般性的, 以(1+n)/2为对称轴, 每个左侧区间都唯一对应一个右侧区间, 并且二者权值的
        平均值恰为(1+n)/2
        那么问题就转化为求出有多少个奇数节点k
        这些奇数节点有且只有两种情况
        (1)奇数节点为[1...n], 这时的权值恰为(1+n)/2, 对k的贡献为1
        (2)其他情况的奇数节点必然会有另一个与之配对, 二者的权值为(1+n), 对k的贡献为2
        综上, 最终统计出k后, 答案就是k*(1+n)/2

    另解(jiangly思路):
        jls是只利用最左端的节点(即以1为左端点的节点)
        其他节点利用计算偏移量来推导, 也能在logn时间内计算出
*/
void solve1(){
    ll n, k;
    cin >> n >> k;
    ll cnt = 1, delta = 0, ans = 0;
    while(n >= k) {
        if(n % 2 == 0) {
            n >>= 1;
            delta = delta * 2 + cnt * n;
            cnt <<= 1;
        } else {
            ans += (1 + n) / 2 * cnt + delta;
            n >>= 1;
            delta = delta * 2 + cnt * (n + 1);
            cnt <<= 1;
        }
    }
    cout << ans << "\n";
}
void solve2(){
    ll n, k;
    cin >> n >> k;
    ll t = n, count = 0, cur = 0;
    while(t >= k){
        if(t & 1){
            count += (1LL << cur);
        }
        t >>= 1;
        cur += 1;
    }
    cout << count * (1 + n) / 2 << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve2();
    }
    return 0;    
}
