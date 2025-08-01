#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://atcoder.jp/contests/abc413/tasks/abc413_g
/*
    构造 || 图论 || 并查集
    题意:
        给定一个N×M的网格图, 其中有K个障碍(X[i], Y[i])
        你可以进行任意次上左下右的移动, 但不能移动到网格外或障碍上
        判断能否从(1,1)走到(N,M)
        范围: N∈[1,2e5], M∈[1,2e5], K∈[0,2e5], 保证所有障碍互不相同且不位于(1,1)和(N,M)
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        我们思考障碍的性质: 什么时候两个障碍能够形成配合?
        不难发现, 障碍是八连通的, 当两个障碍的切比雪夫距离为1的时候, 就可以联合起来形成更大的防线
        问题在于, 如何进一步判定防线能否堵住所有路线呢?
        换句话说, 从起点到中点的所有路线都与障碍形成的防线相交
        根据线段相交的知识, 障碍形成的防线的两个端点必须一个在路线的左侧, 一个在路线的右侧
        考虑极端情况, 路线沿着边缘走, 此时得到了关键结论: 防线必须在边缘处有点
        我们考虑网格图的左侧和下侧边缘任取一点u, 右侧和上侧边缘任取一点v
        如果u和v进行连线, 我们发现这样一定能堵住所有路线, 因为这完全把网格图的(1,1)和(N,M)划分开了
        因此我们就得到了解法:
        利用并查集, 按照八连通把所有障碍合并起来
        如果存在右侧和上侧的障碍u与左侧和下侧的障碍v连通, 那么我们一定走不到(N,M)
        否则说明中间有空隙, 一定能走到(N,M)
*/
vector<int> fa;
int find(int o) { return o == fa[o] ? fa[o] : fa[o] = find(fa[o]); }
void merge(int u, int v) { fa[find(u)] = find(v); }
struct info {
    int x, y;
};
int dx[8] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[8] = {1, 0, -1, 0, 1, -1, 1, -1};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    fa.resize(k + 1);
    iota(fa.begin(), fa.end(), 0);
    vector<info> a(k + 1);
    map<PII, int> mp;
    for(int i = 1; i <= k; i++) {
        cin >> a[i].x >> a[i].y;
        mp[{a[i].x, a[i].y}] = i;
    }
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        for(int s = 0; s < 8; s++) {
            int nx = x + dx[s], ny = y + dy[s];
            if(nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if(mp[{nx, ny}]) {
                merge(i, mp[{nx, ny}]);
            }
        }
    }
    bool ok = true;
    vector<int> vis(k + 1);
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        if(x == 1 || y == m) {
            vis[find(i)] = true;
        }
    }
    for(int i = 1; i <= k; i++) {
        auto [x, y] = a[i];
        if(x == n || y == 1) {
            if(vis[find(i)]) {
                ok = false;
                break;
            }
        } 
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}


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
 