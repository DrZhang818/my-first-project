#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2096/problem/D
/*
    构造 || 数学
    题意:
        在一个无限大的二维平面上, 每个点都放置了一个灯泡
        起初只有坐标(s,t)的灯泡是亮的, 表示这个位置有宝藏!
        为了隐藏宝藏位置, 你进行了任意次下列操作:
        op: 选择两个整数x,y, 切换(x,y),(x,y+1),(x+1,y-1),(x+1,y)的灯泡状态
        最终得到了当前状态: 给定N个点(xi,yi), 表示当前状态下(xi,yi)的灯泡是亮着的
        很不幸的是, 你忘记了宝藏藏在哪个位置了, 请你找出宝藏位置的一个可行解
        题目数据保证至少有一个可行解
        范围: N∈[1,2e5], x,y∈[-1e8,1e8], s,t∈[-1e9,1e9]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一半
        首先观察题目性质, 我们自然想到把问题建模为一个01矩阵上的翻转操作
        对于这种问题, 经验告诉我们往往涉及到异或操作, 进而产生出奇偶性等系统不变量
        进而我们会发现, x = s的这条线必有奇数个灯泡, x != s的线必然有偶数个灯泡
        这是因为我们的操作对x和x + 1同时翻转两个灯泡, 因此奇偶性不变
        另一个不变量比较难以发现, 即对角线x + y的奇偶性保持不变
        如果我们把这操作的四个点画出来并连线, 我们就能发现它们构成了一个平行四边形
        这样就能更容易地发现这个不变量, 不过要想快速找出来, 还需要大量的做题经验
*/

void solve() {
    int n;
    cin >> n;
    int x = 0, diag = 0;
    for(int i = 1; i <= n; i++) {
        int u, v;
        cin >> u >> v;
        x ^= u;
        diag ^= (u + v);
    }
    cout << x << " " << diag - x << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
