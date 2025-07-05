#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2113/problem/B
/*
    构造 || 思维
    题意:
        给定一个N×M的矩形, 左下角为(0,0)点, 你需要用大小为a×b的木板覆盖这个矩形, 并满足:
        (1)木板不能旋转
        (2)木板不能重叠
        (3)木板可以超出矩形边界
        现在矩阵中已经放置了两个木板, 请你判断能否在不移除这两块木板的情况下完全覆盖这个矩形
        范围: N,M,a,b∈[1,1e9], x1,x2∈[-a+1, w-1], y1,y2∈[-b+1, h-1]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 对于这种判断是否存在解的问题, 我们首先思考合法解有哪些性质
        假设不存在这两块木板, 我们考虑所有合法放置方案, 它们有哪些共同的特征呢?
        关键观察: 两个邻接(有公共边)的木板, 记左下角坐标为(x1,y1),(x2,y2), 则必有:
                    x1 ≡ x2 (mod a) 或 y1 ≡ y2 (mod b)
        下面讨论都以两个木板为上下邻接关系进行讨论, 不妨y1 < y2
        (1)如果x1 != x2, 这时两个木板为错位邻接关系, 不难发现, 此时两个木板所在的两层
            会强制性地被确定下来, 这些木板与原来两个木板都满足y坐标模b相同
        (2)如果x1 = x2, 此时既满足x1 ≡ x2 (mod a)又满足 y1 ≡ y2(mod b)
            可以把这两个木板看成一个, 递归地讨论与这个木板邻接的其他木板
        这样我们就总结出一个性质:
            对于任意两个木板, 必然满足x1 ≡ x2 (mod a) 或 y1 ≡ y2 (mod b)
        因此对于给定的两个木板, 必须要满足x1 ≡ x2 (mod a) 或 y1 ≡ y2 (mod b)
        特判x1 = x2或y1 = y2的情况
        充分性:
            如果满足x1 ≡ x2 (mod a) 或 y1 ≡ y2 (mod b), 则一定存在一种合法构造
            因为x1 ≡ x2 (mod a)时候可以按列放置, y1 ≡ y2 (mod b)可以按行放置
*/

bool same(int u, int v, int m) {
    return (u % m + m) % m == (v % m + m) % m;
}
void solve() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    bool ok = false;
    if(x1 == x2) {
        ok = same(y1, y2, b);
    } else if(y1 == y2) {
        ok = same(x1, x2, a);
    } else {
        ok = same(x1, x2, a) | same(y1, y2, b);
    }
    ok ? puts("Yes") : puts("No");
}

// void solve() {
//     int n, m, a, b;
//     cin >> n >> m >> a >> b;
//     int x1, y1, x2, y2;
//     cin >> x1 >> y1 >> x2 >> y2;
//     int x3 = x1 + a, x4 = x2 + a;
//     int y3 = y1 + b, y4 = y2 + b;
//     bool ok = false;
//     int dx = max(x1, x2) - min(x3, x4);
//     int dy = max(y1, y2) - min(y3, y4);
//     if((dx >= 0 && dx % a == 0) || (dy >= 0 && dy % b == 0)) ok = true;
//     if(ok) {
//         cout << "YES\n";
//     } else {
//         cout << "NO\n";
//     }
// }

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
