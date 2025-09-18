#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/1288/E
/*
    数据结构 || 思维
    题意:
        给定一个1~N的排列P, 初始P[i] = i, 你需要处理M次操作
        op: 给定x, 设P[i] = x, 将排列更新为 P[i],P[1],P[2],...,P[i-1],P[i+1],...,P[N]
            简单来说, 将x移动到排列开头, 将在x前面的元素依次向后移位
        对于每个x∈[1,N], 你需要回答在移动过程中 x 出现的最小位置和最大位置
        范围: N∈[1,3e5], M∈[1,3e5], a[i]∈[1,N]
    关键思考:
        本题为数据结构类题目, 需要读清题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先思考题目性质, 最小位置是容易确定的, 因为操作只会让其他元素的位置变得更大, 
        因此对于元素x来说, 如果它被操作过, 最小位置就是1, 否则最小位置就是初始位置x
        下面思考如何求解最大位置呢?
        设元素x被操作了k次, 由上面操作的性质可知, 在任意两个相邻操作之间, 位置是单调不降的
        因此最大值必然是某次操作前的那个时刻达到的
        所以问题就转化成: 操作x之前, 查询一下此时x的位置, 并更新最大值
        如果暴力维护每个元素的实时位置, 复杂度为O(NM), 显然超时
        换个思路: 我们发现 x 的位置等价于x前面(含x)有多少个元素, 即有多少个pos[y] <= pos[x] 
        这启发我们用树状数组来维护
        操作的本质是把当前的x删除, 再在数组开头插入x
        如果直接把pos[x]设为1, 就会占用原来在1位置的元素, 依次顺延的复杂度还是O(N)的
        于是我们用个巧妙的trick, 开N + M个位置, 初始时1~N排列在 M+1 ~ M+N
        之后第i次操作就是把pos[x]更改为 M - i + 1
        这样就能完美表示出这种相对位置关系
        利用树状数组, 每次更新把tr[pos[x]]减1, 把tr[M - i + 1]加1
        这样就能在O(logn)时间内修改/查询pos[x]的位置了
*/

inline int lowbit(int o) { return o & -o; }
int sz;
vector<int> tr;
void add(int o, int d) {
    for(; o <= sz; o += lowbit(o)) {
        tr[o] += d;
    }
}
int query(int o) {
    int res = 0;
    for(; o > 0; o -= lowbit(o)) {
        res += tr[o];
    }
    return res;
}

void solve() {
    int n, m;
    cin >> n >> m;
    sz = n + m;
    tr.resize(sz + 1);
    vector<int> mn(n + 1), mx(n + 1), pos(n + 1);
    for(int i = 1; i <= n; i++) {
        add(m + i, 1);
        mn[i] = mx[i] = i;
        pos[i] = m + i;
    }
    for(int i = 1; i <= m; i++) {
        int x;
        cin >> x;
        mn[x] = 1;
        mx[x] = max(mx[x], query(pos[x]));
        add(pos[x], -1);
        pos[x] = m - i + 1;
        add(pos[x], 1);
    }
    for(int x = 1; x <= n; x++) {
        mx[x] = max(mx[x], query(pos[x]));
    }
    for(int x = 1; x <= n; x++) {
        cout << mn[x] << " " << mx[x] << "\n";
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
