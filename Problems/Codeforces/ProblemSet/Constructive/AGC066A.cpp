#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/agc066/tasks/agc066_a
/*
    构造 || 数论
    题意:
        给定一个N×N的矩阵, 你可以进行以下操作:
        op: 选择i,j,x, 将x加到a[i][j]上, 代价为 |x|
        定义矩阵是合法的, 当且仅当任意相邻两项的绝对差 >= d
        你需要用总代价不超过dN^2/2的操作使得矩阵合法, 输出操作后得到的矩阵
        范围: N∈[2,500], d∈[1,1000], a[i][j]∈[-1000,1000]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        我们先来思考easy版本, 如果原始矩阵为全0矩阵, 如何实现这一目标呢?
        显然, 我们有种简单的构造方式:
            将矩阵进行黑白染色, (i + j)为奇数的格子修改为d即可
            0 d 0 d...
            d 0 d 0...
            ..........
        此外, 我们也可以把(i + j)为偶数的格子修改为d
            d 0 d 0...
            0 d 0 d...
            ..........
        这其实我们把矩阵按照类似黑白染色的方式进行修改
        但是问题在于, 如果把矩阵统一变为上面的形式, 显然会超过题目要求
        因为很多情况下, 如果两个数已经符合要求, 那么我们就不用再调整了
        这里有个关键观察:
            对于上面的矩阵, 任意元素加上或减去k * (2d)后仍是合法的
        这说明, 我们只要在mod 2d意义下把原矩阵转化成上面两种即可
        如何证明这两种方式必有一种的操作次数合法呢?
        我们发现, 对于任意x, 将其调整为mod 2d等于0 和 mod 2d = d的次数是互补的, 总和恰好为d
        因此第一种方式和第二种方式的总次数为 dN^2
        那么必有一种的操作次数 <= floor(dN^2 / 2), 必有一种的操作次数 >= ceil(dN^2 / 2)
        从而说明存在符合条件的构造方式, 我们只需要枚举一下这两种方式取最小值即可
        
        如何求 把 x + t ≡ y (mod p) 的最小非负整数解 与 最大负整数解 ?
        很简单, (y - x) mod p就是最小非负整数解, [(y - x) mod p] - p就是最大负整数解
*/
int get(int x, int y, int p) {
    int t = ((y - x) % p + p) % p;
    return min(t, p - t);
}
void solve() {
    int n, d;
    cin >> n >> d;
    vector a(n + 1, vector<int>(n + 1));
    ll sum1 = 0, sum2 = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cin >> a[i][j];
            int tar = (i + j) % 2 == 1 ? 0 : d;
            sum1 += get(a[i][j], tar, 2 * d);
            sum2 += get(a[i][j], d - tar, 2 * d);
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            int x, tar;
            if(((i + j) % 2 == 1) ^ (sum1 >= sum2)) {
                tar = 0;
            } else {
                tar = d;
            }
            int p = 2 * d;
            int t = ((tar - a[i][j]) % p + p) % p;
            if(t < p - t) {
                a[i][j] += t;
            } else {
                a[i][j] -= p - t;
            }
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << a[i][j] << " \n"[j == n];
        }
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
