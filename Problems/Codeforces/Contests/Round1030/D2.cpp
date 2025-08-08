 #include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2118/problem/D2
/*
    DP || 数论 || 图论
    题意:
        给定一个长度为10^15的带状区域和常数k, 区域内有n个红绿灯, 每个信号灯位置为p[i], 初始延迟为d[i]
        满足d[i] < k, 第i个信号灯的工作方式如下:
            当秒数t mod k = d[i]时显示红灯
            其余时间显示绿灯
        在第0秒, 你从带状区域的某个单元格出发, 初始面朝正方向, 每秒按以下顺序执行动作:
            若当前单元格有红灯, 立即调头
            沿当前朝向移动一个单元格
        给定q个不同的起始位置a, 对于每个起始位置, 判断你能否在10^100秒内离开带状区域
        范围: n∈[1,2e5], k∈[1,1e15], 1 <= p[1] < p[2] <...< p[n] <= 1e15, d[i]∈[0,k-1]
              q∈[1,2e5], a[i]∈[1,1e15]
    关键思考:
        本题为模拟类题目, 需要读请题意, 选用合适的算法和数据结构维护题目信息, 回答询问
        首先观察题目性质, 由于每k秒是一个循环, 因此我们只需要研究一个循环节即可
        10^100秒可以视为无限长时间, 我们判断能否逃出带状区域, 就是看是否进入到某个环当中
        对于每个信号灯, 一共可以拆分为四种状态: 正向到达红灯, 反向到达红灯, 正向到达绿灯, 反向到达绿灯
        显然, 如果到达该点时为绿灯, 相当于什么都没发生, 因此我们可以忽略这两种绿灯的状态
        如果是正向到达红灯, 我们就会调转方向
        此时问题就变成了: 从当前位置当前时刻, 反向走能否直接走出去 or 反向走到哪会遇到红灯
        如果我们反向走会遇到红灯, 那我们就可以把正向到达红灯i向反向到达红灯j连一条有向边
        这条边的含义是: 正向到达i能否走出去取决于反向到达j能否走出去
        对于反向到达红灯同理, 我们需要看从当前位置当前时刻正向走能否走出去 or 正向走会到哪遇到红灯
        为了描述正向与反向这两种状态, 我们可以进行拆点, 把1~n设为正向, n+1~2n设为反向
        建好图后, 我们需要判断这2n个点中, 哪些点是无法逃逸的
        对问题进行转化, 等价于判断哪些点可以走到出度为0的点, 这是一个连通性问题
        我们可以建反图, 从出度为0的点bfs, 所有被访问过的点就是与其连通的点, 这些点均可以逃逸
        本题由于每个点出度最大为1, 因此我们可以直接用nxt数组存储下一个点的编号

        接下来的问题是, 如何快速求解每个状态的下一个状态呢?
        我们首先考虑正向到达红灯, 求解其第一个反向到达的红灯
        我们设当前是第i个信号灯, 当前时刻为t, 第一个反向到达的红灯是j
        由于当前是红灯, 因此要满足 t % k = d[i]
        由于反向到达的也是红灯, 因此要满足 (t + p[i] - p[j]) % k = d[j]
            由t % k = d[i]可知, t = a * k + d[i]
            代入到第二个等式:
            (a * k + d[i] + p[i] - p[j]) % k = d[j]
            化简得 (d[i] + p[i] - p[j]) % k = d[j]
            即     d[i] + p[i] - p[j] ≡ d[j] ( mod k )                        
                   d[i] + p[i] ≡ d[j] + p[j] ( mod k )
        因此我们可以按 d[i] + p[i] 对k的余数进行分组, 用map存储该组最新的下标编号, 这便是i反向
        到达的第一个红灯j

        下面考虑反向到达红灯, 思路基本一致
        设当前是第i个信号灯, 当前时刻为t, 第一个正向到达的红灯是j
        由于当前是红灯, 因此要满足 t % k = d[i]
        由于正向到达的也是红灯, 因此要满足 (t + p[j] - p[i]) % k = d[j]
            由t % k = d[i]可知, t = a * k + d[i]
            代入到第二个等式:
            (a * k + d[i] + p[j] - p[i]) % k = d[j]
            化简得 (d[i] + p[j] - p[i]) % k = d[j]
            即     d[i] + p[j] - p[i] ≡ d[j] ( mod k )
                   d[i] - p[i] ≡ d[j] - p[j] ( mod k )
        因此我们可以按 d[i] - p[i] 对k的余数进行分组

        这样就预处理好了这2n个点哪些能出去哪些不能出去
        下面考虑如何进行查询
        给定位置为x, 时刻为0, 我们要求解第一个正向到达的红灯i是谁
        由于i是红灯, 因此要满足 (p[i] - x) % k = d[i]
            即 p[i] - x ≡ d[i] ( mod k )
               x ≡ p[i] - d[i] ( mod k )
        因此我们可以按 p[i] - d[i] 进行分组, 组内存储{p[i], i}
        这样在查询时, 我们就可以在x % k这个组中二分找第一个 >= x的p[i], 对应的i就是我们要找的红灯
*/      

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<ll> p(n + 1), d(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    vector<int> nxt(2 * n + 1);
    map<ll,int> mp;
    for(int i = 1; i <= n; i++) {
        ll rem = (d[i] + p[i]) % k;
        if(mp.contains(rem)) {
            nxt[i] = n + mp[rem];
        }
        mp[rem] = i;
    }
    mp.clear();
    for(int i = n; i >= 1; i--) {
        ll rem = (d[i] - p[i] % k + k) % k;
        if(mp.contains(rem)) {
            nxt[i + n] = mp[rem];
        }
        mp[rem] = i;
    }
    vector<vector<int>> adj(2 * n + 1);
    queue<int> que;
    vector<bool> outs(2 * n + 1);
    for(int i = 1; i <= 2 * n; i++) {
        if(!nxt[i]) {
            outs[i] = true;
            que.push(i);
        } else {
            adj[nxt[i]].push_back(i);
        }
    }
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int v : adj[u]) {
            outs[v] = true;
            que.push(v);
        }
    }
    map<ll,vector<pair<ll,int>>> pos;
    for(int i = 1; i <= n; i++) {
        ll rem = (p[i] - d[i] + k) % k;
        pos[rem].emplace_back(p[i], i);
    }
    int q;
    cin >> q;
    while(q--) {
        ll x;
        cin >> x;
        ll rem = x % k;
        if(pos[rem].empty()) {
            cout << "YES\n";
            continue;
        }
        auto it = lower_bound(pos[rem].begin(), pos[rem].end(), pair(x, 0));
        if(it == pos[rem].end()) {
            cout << "YES\n";
            continue;
        }
        int i = it->second;
        if(outs[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}


// void solve() {
//     ll n, k;
//     cin >> n >> k;
//     vector<ll> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     vector<ll> d(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> d[i];
//     }
//     map<ll,int> mp1, mp2;
//     vector<vector<int>> adj(2 * n + 1);
//     for(int i = 1; i <= n; i++) {
//         ll rem = (a[i] + d[i]) % k;
//         if(mp1.count(rem)) {
//             adj[i].push_back(mp1[rem] + n);
//         }
//         mp1[rem] = i;
//     }
//     for(int i = n; i >= 1; i--) {
//         ll rem = ((d[i] - a[i]) % k + k) % k;
//         if(mp2.count(rem)) {
//             adj[i + n].push_back(mp2[rem]);
//         }
//         mp2[rem] = i;
//     }
//     vector<int> dfn(2 * n + 1), low(2 * n + 1), scc(2 * n + 1), c(2 * n + 1);
//     int timer = 0, cnt = 0;
//     stack<int> stk;
//     auto dfs = [&](this auto &&self, int u) -> void {
//         dfn[u] = low[u] = ++timer;
//         stk.push(u);
//         for(int v : adj[u]) {
//             if(!dfn[v]) {
//                 self(v);
//                 low[u] = min(low[u], low[v]);
//             } else if(!scc[v]) {
//                 low[u] = min(low[u], dfn[v]);
//             }
//         }
//         if(dfn[u] == low[u]) {
//             ++cnt;
//             while(1) {
//                 int v = stk.top(); stk.pop();
//                 scc[v] = cnt;
//                 c[cnt]++;
//                 if(v == u) break;
//             }
//         }
//     };
//     for(int i = 1; i <= n; i++) {
//         if(!dfn[i]) {
//             dfs(i);
//         }
//     }
//     map<ll,set<int>> mp;
//     for(int i = 1; i <= n; i++) {
//         ll rem = ((a[i] - d[i]) % k + k) % k;
//         mp[rem].insert(i);
//     }
//     int q;
//     cin >> q;
//     while(q--) {
//         ll x, y;
//         cin >> x;
//         y = x % k;
//         int i = lower_bound(a.begin() + 1, a.end(), x) - a.begin();
//         if(mp[y].size() == 0) {
//             cout << "YES\n";
//         } else {
//             auto it = mp[y].lower_bound(i);
//             if(it == mp[y].end() || c[scc[*it]] == 1) {
//                 cout << "YES\n";
//             } else {
//                 cout << "NO\n";
//             }
//         }
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
