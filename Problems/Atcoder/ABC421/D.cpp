#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<ll,ll> PLL;
typedef unsigned long long ull;
const ll inf = 1E18;

//https://atcoder.jp/contests/abc421/tasks/abc421_d
/*
    计算几何 || 模拟
    题意:
        在无限大二维网格中, Alice起始在(x1,y1), Bob起始在(x2,y2), 二人即将同时进行N次移动操作
        给定两个长度为N的字符串S和T, S表示Alice的移动策略, T表示Bob的移动策略
        由于N过大, S和T将被分别分割成M段和L段, 从左到右每一段由(C,x)给出, 表示由x个C字符组成
        求N次移动过程中, 有多少次移动满足: 移动后Alice和Bob恰好站在同一个格子里
        范围: N∈[1,1e14], x1,y1,x2,y2∈[-1e9,1e9], M,L∈[1,1e5], x∈[1,1e9]
    关键思考:
        本题为模拟类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先思考暴力做法, 直接做N次移动并判断, 时间复杂度为O(N), 超时
        我们发现, 由于M和L不大, 因此可以考虑使用扫描线进行处理
        每次取出S当前段和T当前段, 取二者长度的较小值mn, 那么这mn次操作就可以合并为1次操作
        观察操作的性质, 我们按照当前Alice和Bob的位置可以分出以下三种情况:
        (1)若x1 = x2 且 y1 = y2:
            此时只需关注二人的操作策略是否相同
            1.如果操作策略相同, 那么接下来的mn次二人都会在同一格
            2.如果操作策略不同, 那么接下来的mn次二人都不会在同一格
        (2)若二人移动方向垂直:
            此时只需关注二人能否同时到达交汇位置(px,py)
            为方便起见, 我们不妨设Alice横向移动, Bob纵向移动
            那么必有(px,py) = (x1, y2)
            1.若y1 <= py && ny1 < py || y1 >= py && ny1 > py:
                此时Alice的移动过程中一定不会落在(px,py)
            2.若x2 <= px && nx2 < px || x2 >= px && nx2 > px:
                此时Bob的一定过程中一定不会落在(px,py)
            3.若abs(y1 - py) ≠ abs(x2 - px):
                此时Alice和Bob一定不会在同一时刻到达(px,py)
            判掉以上三种情况后, 我们就可以将答案 + 1
        (3)若二人移动方向平行:
            此时只需关注二人能否同时到达交汇位置(px,py)
            不妨以二人水平移动为例:
            1.若x1 ≠ x2, 说明两人根本不在一条线上移动, 直接否掉
            2.若abs(y1 - y2) % 2 != 0, 说明二人所在格子的奇偶性永远不同, 否掉
            3.若y1 < x2 && ny1 >= ny2, 说明此时Alice在向右走, Bob在向左走, 且确实有交点
                因此答案 + 1
            4.若y1 > y2 && ny1 <= ny2, 说明此时Alice在向左走, Bob在向右走, 且确实有交点
                因此答案 + 1
*/
struct info {
    char c;
    ll cnt;
};
bool ck(char x, char y) {
    bool ok = false;
    if((x == 'U' || x == 'D') && (y == 'L' || y == 'R')) {
        ok = true;
    }
    if((y == 'U' || y == 'D') && (x == 'L' || x == 'R')) {
        ok = true;
    }
    return ok;
}
PLL get(PLL cur, char c, ll t) {
    if(c == 'U') cur.first -= t;
    else if(c == 'D') cur.first += t;
    else if(c == 'L') cur.second -= t;
    else cur.second += t;
    return cur;
}
void solve() {
    ll x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ll n, m, l;
    cin >> n >> m >> l;
    vector<info> a(m + 1), b(l + 1);
    for(int i = 1; i <= m; i++) {
        cin >> a[i].c >> a[i].cnt;
    }
    for(int i = 1; i <= l; i++) {
        cin >> b[i].c >> b[i].cnt;
    }
    int i = 1, j = 1;
    ll ans = 0;
    while(i <= m && j <= l) {
        ll mn = min(a[i].cnt, b[j].cnt);
        auto [nx1, ny1] = get({x1, y1}, a[i].c, mn);
        auto [nx2, ny2] = get({x2, y2}, b[j].c, mn);

        if(x1 == x2 && y1 == y2) {
            if(a[i].c == b[j].c) {
                ans += mn;
            }
        } else {
            if(ck(a[i].c, b[j].c)) {
                ll px, py;
                bool ok = true;
                char op1 = a[i].c, op2 = b[j].c;
                if(b[j].c == 'L' || b[j].c == 'R') {
                    swap(x1, x2);
                    swap(y1, y2);
                    swap(nx1, nx2);
                    swap(ny1, ny2);
                    swap(op1, op2);
                }
                px = x1;
                py = y2;
                if(y1 <= py && ny1 < py || y1 >= py && ny1 > py) {
                    ok = false;
                }
                if(x2 <= px && nx2 < px || x2 >= px && nx2 > px) {
                    ok = false;
                }
                if(abs(py - y1) != abs(px - x2)) {
                    ok = false;
                }
                if(ok) {
                    ans++;
                }
                if(b[j].c == 'L' || b[j].c == 'R') {
                    swap(x1, x2);
                    swap(y1, y2);
                    swap(nx1, nx2);
                    swap(ny1, ny2);
                }
            } else {
                if(a[i].c == 'L' || a[i].c == 'R') {
                    if(x1 == x2 && abs(y1 - y2) % 2 == 0 && (y1 < y2 && ny1 >= ny2 || y1 > y2 && ny1 <= ny2)) {
                        ans++;
                    } 
                } else {
                    if(y1 == y2 && abs(x1 - x2) % 2 == 0 && (x1 < x2 && nx1 >= nx2 || x1 > x2 && nx1 <= nx2)) {
                        ans++;
                    }
                }
            }
        }
        x1 = nx1;
        y1 = ny1;
        x2 = nx2;
        y2 = ny2;
        a[i].cnt -= mn;
        b[j].cnt -= mn;
        if(a[i].cnt == 0) {
            i++;
        }       
        if(b[j].cnt == 0) {
            j++;
        }
    }
    cout << ans << "\n";
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
