from pathlib import Path
import json,subprocess,re
ROOT=Path(__file__).resolve().parents[1]
path=ROOT/'source/handbook.json';book=json.loads(path.read_text(encoding='utf-8'))
OUT=ROOT/'examples';OUT.mkdir(exist_ok=True)
examples={}
def ex(i,title,code,more='',deps=()):
    examples.setdefault(i,[]).append(dict(title=title,code=code.strip(),more=more,deps=list(deps)))
ex(6,'Info：区间和与前缀找第 k 个',r'''
struct Info {
    long long sum = 0;
    Info operator+(Info b) const { return {sum + b.sum}; }
};
int main() {
    vector<Info> a = {{0}, {2}, {0}, {3}};
    Seg<Info> s(a);
    assert(s.query(1, 3).sum == 5);
    int p = s.first(1, 3, [](Info x) { return x.sum >= 3; });
    assert(p == 3); // 频次必须非负，判定才单调。
}
''')
ex(7,'Info / Tag：区间仿射与区间和',r'''
const int P = 998244353;
struct Tag {
    long long mul = 1, add = 0;
    void apply(Tag t) {
        mul = mul * t.mul % P;
        add = (add * t.mul + t.add) % P;
    }
};
struct Info {
    long long sum = 0;
    int len = 0;
    void apply(Tag t) { sum = (sum * t.mul + t.add * len) % P; }
    Info operator+(Info b) const { return {(sum + b.sum) % P, len + b.len}; }
};
int main() {
    vector<Info> a = {{0, 0}, {1, 1}, {2, 1}, {3, 1}};
    LazySeg<Info, Tag> s(a);
    s.apply(1, 3, {2, 1}); // x -> 2x+1，得到 3,5,7。
    s.apply(2, 3, {0, 4}); // 赋值为4；加c用 {1,c}。
    assert(s.query(1, 3).sum == 11);
}
''','叶子 len=1，单位元 len=0；初始化 LazySeg(n) 的默认 Info 没有实际区间长度，不能直接用于此 Info。输入与 Tag 的模值先归一化。')
ex(8,'前缀版本：静态区间第 k 小',r'''
struct Info {
    int sum = 0;
    void apply(Info b) { sum += b.sum; }
    Info operator+(Info b) const { return {sum + b.sum}; }
    Info operator-(Info b) const { return {sum - b.sum}; }
};
int main() {
    vector<int> a = {0, 5, 1, 5, 3}, v(a.begin() + 1, a.end());
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int n = a.size() - 1, m = v.size();
    PST<Info> s(m, n);
    vector<int> rt(n + 1);
    for(int i = 1; i <= n; i++) {
        int x = lower_bound(v.begin(), v.end(), a[i]) - v.begin() + 1;
        rt[i] = s.modify(rt[i - 1], x, {1});
    }
    int l = 2, r = 4, k = 2; // 闭区间；k需合法。
    int x = s.first(rt[l - 1], rt[r], 1, m,
                    [&](Info t) { return t.sum >= k; });
    assert(v[x - 1] == 3);
}
''','输入位置和值域下标是两套编号，rt[i] 是前 i 个元素形成的值域频率版本。减根的顺序为 rt[r]-rt[l-1]。')
ex(9,'动态开点：点赋值',r'''
struct Info {
    long long sum = 0;
    Info operator+(Info b) const { return {sum + b.sum}; }
};
int main() {
    DynSeg<Info> s(-1000000000, 1000000000);
    int rt = 0;
    s.modify(rt, -7, {3});
    s.modify(rt, 12, {5});
    s.modify(rt, 12, {1});
    assert(s.query(rt, -10, 20).sum == 4);
}
''')
ex(12,'完整 Policy：区间加、反转、求和',r'''
struct Policy {
    using Val = long long;
    using Info = long long;
    using Tag = long long;
    static Info identity() { return 0; }
    static Tag tagIdentity() { return 0; }
    static bool tagEmpty(Tag t) { return t == 0; }
    static Info make(Val v) { return v; }
    static Info merge(Info a, Info b) { return a + b; }
    static void apply(Val& v, Info& sum, int len, Tag t) {
        v += t;
        sum += len * t;
    }
    static void compose(Tag& a, Tag b) { a += b; }
    static void reverseInfo(Info&) {} // 和与方向无关，才能留空。
};
int main() {
    Treap<Policy> s;
    int rt = s.build(vector<long long>{1, 2, 3, 4}); // build为0-based。
    s.apply(rt, 2, 4, 10);
    s.rangeReverse(rt, 1, 3);
    assert(s.query(rt, 1, 2) == 25);
    int t = s.erase(rt, 2, 3);
    s.insert(rt, 0, t);
    assert(s.size(rt) == 4);
}
''','split(rt,k) 拆成前 k 个和余下；merge 只按顺序拼接。若维护字符串哈希，Info 要存正反两个哈希，reverseInfo 交换它们。')
ex(14,'斜率任意顺序：最小直线值',r'''
int main() {
    LiChao s(-1000000, 1000000);
    s.addLine(3, 5);
    s.addLine(-2, 1);
    assert(s.query(7) == -13);
}
''')
ex(15,'转移 dp[i]=min(dp[j]+(i-j)²)',r'''
int main() {
    CHT s;
    vector<long long> dp(9);
    s.addPoint({0, 0});
    for(int i = 1; i <= 8; i++) {
        dp[i] = (long long)(s.query({-2LL * i, 1}) + 1LL * i * i);
        s.addPoint({i, dp[i] + 1LL * i * i});
    }
    assert(dp[8] == 8);
}
''','把候选 j 写成点 (j,dp[j]+j²)，查询向量(-2i,1)，常数 i² 最后加；插入点横坐标递增。')
ex(17,'动态树点权异或',r'''
int main() {
    LCT s(3);
    for(int i = 1; i <= 3; i++) s.setValue(i, i);
    assert(s.link(1, 2) && s.link(2, 3));
    assert(s.pathXor(1, 3) == (1 ^ 2 ^ 3));
    assert(!s.link(1, 3));
    assert(s.cut(1, 2));
    assert(!s.connected(1, 3));
}
''')
ex(27,'析取与固定变量',r'''
int main() {
    TwoSAT s(2);
    s.addClause(1, true, 2, false); // x1 或 非x2。
    s.setValue(1, false);
    assert(s.solve());
    assert(!s.answer[1] && !s.answer[2]);
}
''')
ex(32,'最大匹配与最小点覆盖',r'''
int main() {
    HK s(3, 3);
    s.addEdge(1, 1); s.addEdge(1, 2);
    s.addEdge(2, 2); s.addEdge(3, 2);
    assert(s.solve() == 2);
    auto [a, b] = s.minVertexCover();
    assert(a.size() + b.size() == 2);
    for(int u = 1; u <= 3; u++) {
        if(s.left[u]) cout << u << ' ' << s.left[u] << '\n';
    }
}
''','最小点覆盖：从未匹配左点出发，走未匹配边到右边，再走匹配边回左边；取未到达左点+到达右点。')
ex(34,'读回边流量',r'''
int main() {
    Dinic s(3);
    int id = s.addEdge(0, 1, 5);
    s.addEdge(1, 2, 3);
    assert(s.maxFlow(0, 2) == 3);
    assert(5 - s.g[0][id].cap == 3);
    s.addEdge(1, 2, 2);
    assert(s.maxFlow(0, 2) == 2); // 本次新增量。
}
''')
ex(35,'指定流量的最小费用',r'''
int main() {
    MCF s(3);
    s.addEdge(0, 1, 2, -3);
    s.addEdge(1, 2, 2, 5);
    auto [f, c] = s.flow(0, 2, 2);
    assert(f == 2 && c == 4);
}
''','要“必须发送 K 流”就检查 f==K；要最大流最小费用则不传 limit。仅需负费用增广直到不划算的建模，不能直接把该接口当最大收益可选流。')
ex(36,'可行环流 / 最大流 / 最小流',r'''
int main() {
    BoundFlow s(3);
    s.addEdge(0, 1, 1, 3);
    s.addEdge(1, 2, 1, 2);
    BoundFlow::Result a, b;
    assert(s.maxFlow(0, 2, a) && a.value == 2);
    assert(s.minFlow(0, 2, b) && b.value == 1);
    assert(a.flow[0] == 2 && b.flow[1] == 1);
    vector<long long> f;
    assert(!s.circulation(f)); // 此图没有回边，无法形成环流。
}
''','下界预流导致 balance[u]-=lo,balance[v]+=lo；balance>0 接 SS→u，<0 接 u→TT。源汇版本加 t→s 的INF边，再跑 SS→TT。可行后读人工边流量为base，删掉人工边的正反残量与超级点关联边；最大再跑 s→t，最小跑 t→s 且 limit=base，以保持非负流值。总需求和与最大流值均应小于 inf。')
ex(37,'把不等式翻译成边',r'''
int main() {
    Diff s(3);
    s.le(2, 1, -3); // x2 >= x1+3。
    s.le(2, 3, 2);  // x3 <= x2+2。
    s.eq(1, 3, 4);  // x3=x1+4。
    vector<__int128> d;
    assert(s.solve(d));
    assert(d[2] - d[1] >= 3 && d[3] - d[1] == 4);
    s.le(1, 3, 3);
    assert(!s.solve(d));
}
''','得到的是一组可行势能；若要让 x1=0，可把全部值减 d[1]，不改变差。要求最小/最大某变量时必须按边方向推导界，不能把任意可行解当最优解。')
ex(39,'点 / 区间到区间的有向边',r'''
int main() {
    RangeGraph s(6);
    s.pointRange(1, 2, 3, 5); // 1→[2,3]，每条权5。
    s.rangePoint(2, 3, 4, 2); // [2,3]→4，权2。
    s.rangeRange(4, 4, 5, 6, 1);
    auto d = s.distances(1);
    assert(d[2] == 5 && d[4] == 7 && d[6] == 8);
}
''','在原点周围走辅助零边只代表集合覆盖；入树与出树方向相反，写错会凭空把一个区间里的点互相连通。')
ex(45,'森林返回值也要检查',r'''
int main() {
    vector<Boruvka::Edge> e = {{1,2,4}, {2,3,1}, {1,3,2}};
    auto a = Boruvka::run(4, e);
    assert(a.weight == 3 && a.comp == 2);
    assert(a.edges.size() == 2); // 第4点孤立，不能当生成树。
}
''')
ex(49,'路径瓶颈查询',r'''
int main() {
    KRT s(4, {{1,2,4}, {2,3,7}, {1,3,10}});
    long long w;
    assert(s.bottle(1, 3, w) && w == 7);
    assert(!s.bottle(1, 4, w));
}
''')
ex(51,'点权路径求和：连接 Seg',r'''
struct Info {
    long long sum = 0;
    Info operator+(Info b) const { return {sum + b.sum}; }
};
int main() {
    HLD h(4);
    h.addEdge(1, 2); h.addEdge(1, 3); h.addEdge(2, 4);
    h.work();
    vector<Info> a(5);
    for(int u = 1; u <= 4; u++) a[h.in[u]] = {u};
    Seg<Info> s(a);
    auto query = [&](int u, int v) {
        long long ans = 0;
        while(h.top[u] != h.top[v]) {
            if(h.dep[h.top[u]] < h.dep[h.top[v]]) swap(u, v);
            ans += s.query(h.in[h.top[u]], h.in[u]).sum;
            u = h.parent[h.top[u]];
        }
        if(h.dep[u] > h.dep[v]) swap(u, v);
        return ans + s.query(h.in[u], h.in[v]).sum;
    };
    assert(query(4, 3) == 10);
}
''','边权存较深端点，最后同链段改为 [in[lca]+1,in[另一点]]，空段跳过；跨链仍包含链头。非交换信息需要分别积累 u/v 两端并反转方向，不能像求和这样随意交换。',deps=('segment_tree.hpp',))
ex(53,'虚树边权与 Steiner 子树长度',r'''
int main() {
    vector<vector<int>> g(6);
    for(auto [u,v] : vector<pair<int,int>>{{1,2},{1,3},{2,4},{2,5}}) {
        g[u].push_back(v); g[v].push_back(u);
    }
    VirtualTree s(g);
    auto [root, e] = s.build({4, 5, 3, 4});
    long long ans = 0;
    for(auto [u,v] : e) ans += s.dis(u, v);
    assert(root == 1 && ans == 4);
}
''','本例算连接所有关键点的最小树边数；若原题必须从固定根出发，就把固定根也加入 keys。做DP时把虚树边建成父→子，反向处理 DFS 序；先确认关键点标记不能被加入的 LCA 混淆。')
ex(55,'子树不同颜色数',r'''
int main() {
    vector<vector<int>> g(5);
    for(int u = 2; u <= 4; u++) g[1].push_back(u), g[u].push_back(1);
    vector<int> color = {0, 1, 1, 2, 2}, cnt(3), ans(5);
    int cur = 0;
    DSUOnTree s(g);
    s.run([&](int u, int d) {
        if(cnt[color[u]]) cur--;
        cnt[color[u]] += d;
        if(cnt[color[u]]) cur++;
    }, [&](int u) { ans[u] = cur; });
    assert(ans[1] == 2 && ans[2] == 1 && cur == 0);
}
''')
ex(56,'点分树：动态染色后的最近点',r'''
int main() {
    vector<vector<int>> g(6);
    for(int u = 2; u <= 5; u++) g[u-1].push_back(u), g[u].push_back(u-1);
    LCA l(g);
    Centroid c(g);
    const int INF = 1000000000;
    vector<int> best(6, INF);
    auto add = [&](int u) {
        for(int x = u; x; x = c.parent[x]) best[x] = min(best[x], l.dis(u, x));
    };
    auto query = [&](int u) {
        int ans = INF;
        for(int x = u; x; x = c.parent[x]) ans = min(ans, best[x] + l.dis(u, x));
        return ans;
    };
    add(1); add(5);
    assert(query(3) == 2 && query(4) == 1);
}
''','每个点更新/查询所有点分祖先。能保证某个分治中心落在原树查询点与最近染色点的路径上，故取最小正确。此实现结合倍增LCA为 O(log² n) 每次；若预存各点到点分祖先的距离可做到 O(log n)。只支持添加染色点，删除要把每个中心 best 改成可删多重集。',deps=('lca.hpp',))
ex(79,'非互素 CRT',r'''
int main() {
    long long r, m;
    int ok = crt({{2,6}, {5,9}}, r, m);
    assert(ok == 1 && r == 14 && m == 18);
    assert(crt({{1,2}, {0,4}}, r, m) == 0);
}
''')
ex(89,'不互素与最小指数',r'''
int main() {
    assert(BSGS::solve(2, 4, 8) == 2);
    assert(BSGS::solve(2, 3, 8) == -1);
    assert(BSGS::solve(0, 0, 7) == 1);
}
''')
ex(90,'列向量：斐波那契',r'''
int main() {
    Matrix a(2, 2);
    a(1,1) = a(1,2) = a(2,1) = 1;
    auto v = power(a, 10) * vector<int>{0, 1, 0};
    assert(v[2] == 55); // [F(11),F(10)]，下标0占位。
}
''')
ex(91,'查询与 i128 输出',r'''
void print(__int128 x) {
    if(x < 0) cout << '-', x = -x;
    if(x >= 10) print(x / 10);
    cout << char('0' + x % 10);
}
int main() {
    DuJiaoSieve s(1000);
    auto [a,b] = s.get(10);
    assert(a == 32 && b == -1);
    print(a); cout << ' ' << b << '\n';
}
''','递推：Φ(n)=n(n+1)/2-Σ块(r-l+1)Φ(n/l)，M(n)=1-Σ块(r-l+1)M(n/l)，都从l=2开始。limit太小会拖慢，太大耗内存；按最大询问选一次预筛并复用对象。')
ex(92,'默认积性函数的调用',r'''
int main() {
    Min25Sieve s(10, 1000000007);
    assert(s.solve() == 263);
}
''','筛得到 g0/g1/g2 分别为不超过商值的质数个数、质数和、平方和；sp0/sp1/sp2 是前 j 个小质数相同前缀。S(x,j) 枚举最小质因子下标>=j的非1整数，先统计质数，再枚举p^e与更大质因子部分；solve 最后补 f(1)=1。g/sp取值本来已模P。')
ex(102,'逆、对数与指数的约定',r'''
int main() {
    vector<int> a = {1, 2, 3};
    auto b = polyInv(a, 8);
    auto c = fpsConvTrunc(a, b, 8);
    c.resize(8);
    assert(c[0] == 1);
    for(int i = 1; i < 8; i++) assert(c[i] == 0);
    auto d = polyExp(polyLog(a, 8), 8);
    a.resize(8);
    assert(d == a);
}
''')
ex(103,'模素数方程：判无解并读答案',r'''
int main() {
    const int P = 101, n = 3, m = 2;
    vector<vector<int>> a = {{0,0,0,0}, {0,1,2,5},
                             {0,2,100,0}, {0,3,1,5}};
    vector<int> w;
    int r = gaussMod(a, P, w);
    bool ok = true;
    for(int i = r + 1; i <= n; i++) if(a[i][m+1]) ok = false;
    assert(ok);
    vector<int> x(m + 1); // 自由变量取0。
    for(int j = 1; j <= m; j++) if(w[j]) x[j] = a[w[j]][m+1];
    assert(x[1] == 1 && x[2] == 2);
}
''','仅求秩而不带右端列：gaussMod(a,P,w,列数)。浮点判矛盾用 abs(rhs)>eps，输入条件很差时加大容差也未必可靠。')
ex(104,'非空子集与第 k 个不同值',r'''
int main() {
    XorBasis s;
    s.insert(1); s.insert(2); s.insert(3);
    unsigned long long x;
    assert(s.zero && s.kth(1, x) && x == 0);
    assert(s.kth(4, x) && x == 3);
    assert(!s.kth(5, x));
}
''')
ex(111,'重复模式、重叠匹配',r'''
int main() {
    AC s;
    int x = s.add("aba"), y = s.add("ba"), z = s.add("aba");
    s.build();
    auto cnt = s.match("ababa");
    assert(cnt[x] == 2 && cnt[y] == 2 && cnt[z] == 2);
}
''')
ex(112,'构建 / 出现次数 / 不同子串 / LCS',r'''
int main() {
    SAM s;
    for(char c : string("ababa")) s.add(c);
    assert(s.distinct() == 9);
    s.count();
    assert(s.occ("aba") == 2 && s.occ("ba") == 2);
    assert(s.occ("ac") == 0);
    assert(s.lcs("cababd") == 4);
    long long ans = 0;
    for(int u = 1; u < int(s.t.size()); u++) {
        ans += s.t[u].len - s.t[s.t[u].fa].len;
    }
    assert(ans == s.distinct());
}
''','cnt先按每个前缀终点统计，再向fa传递，正是endpos大小；查一个串沿ch到达u后cnt[u]即次数。lcs在失配时沿fa跳并把当前长度截到新len，不是只换状态不换长度。要多串广义SAM不能每串简单last=0继续套普通extend。')
ex(113,'SA + height：两后缀 LCP',r'''
int main() {
    SA s("banana");
    int a = s.rk[2], b = s.rk[4];
    if(a > b) swap(a, b);
    int ans = INT_MAX;
    for(int i = a + 1; i <= b; i++) ans = min(ans, s.height[i]);
    assert(ans == 3); // anana 与 ana；多询问用ST预处理height。
}
''')
ex(116,'回文出现次数的应用',r'''
int main() {
    PAM s("ababa");
    s.count();
    long long ans = 0;
    for(int u = 2; u < s.size(); u++) {
        ans = max(ans, 1LL * s.tr[u].len * s.tr[u].cnt);
    }
    assert(s.distinct() == 5 && ans == 6);
}
''')
ex(125,'四条真实边界构成矩形',r'''
int main() {
    vector<Point> p = {{0,0},{3,0},{3,2},{0,2}};
    vector<Line> a;
    for(int i = 0; i < 4; i++) a.emplace_back(p[i], p[(i+1)%4]);
    auto h = halfPlanes(a);
    long double area = 0;
    for(int i = 0; i < int(h.size()); i++) area += cross(h[i], h[(i+1)%h.size()]);
    assert(fabsl(area / 2 - 6) < 1e-10);
}
''')
ex(130,'三维偏序的重复点',r'''
int main() {
    auto a = dominance({{1,1,1}, {1,1,1}, {2,2,2}});
    assert(a == vector<long long>({1,1,2}));
}
''')
ex(131,'修改数组后的区间第 k 小',r'''
int main() {
    using E = KthOffline::Event;
    vector<E> e;
    e.push_back({0,1,5,1,0,0,0,0});
    e.push_back({0,2,1,1,0,0,0,0});
    e.push_back({1,0,0,0,1,2,1,0});
    e.push_back({0,2,1,-1,0,0,0,0});
    e.push_back({0,2,7,1,0,0,0,0});
    e.push_back({1,0,0,0,1,2,1,1});
    auto a = KthOffline().solve(2, e, 2);
    assert(a == vector<int>({1,5}));
}
''','递归按值域中点划分，按时间序扫小值修改并用BIT数询问区间内小值；不足k就送右边且k减去小值数。扫描结束必须回滚BIT；事件分区要稳定，不能排序打乱历史顺序。')
ex(132,'边的生存时间',r'''
int main() {
    OfflineConn s(3, 4);
    s.add(1, 2, 1, 2); // 时刻3删去，所以截止2。
    s.add(2, 4, 2, 3);
    vector<pair<int,int>> ask = {{0,0},{1,3},{1,3},{1,3},{2,3}};
    auto a = s.solve(ask);
    assert(a == vector<int>({0,0,1,0,1}));
}
''','DFS进入时间节点记snapshot，合并覆盖该时间段的边，左右子树结束后恢复snapshot；不能路径压缩，否则撤销记录不够。')
fmt=ROOT/'rebuild/tools/clang_format/data/bin/clang-format.exe'
for i,arr in examples.items():
    for j,x in enumerate(arr):
        p=OUT/f'{book[i]["key"]}_{j+1}.cpp'
        inc=['#include "../code/'+book[i]['code']+'"']+['#include "../code/'+k+'"' for k in x['deps']]
        p.write_text('\n'.join(inc)+'\n'+x['code']+'\n',encoding='utf-8')
        subprocess.run([str(fmt),'-i','--style=file',str(p)],check=True)
        text=p.read_text(encoding='utf-8');x['code']='\n'.join(text.splitlines()[len(inc):])
        x['file']=p.relative_to(ROOT).as_posix()
        if x['more']:book[i]['notes'].append(x['more'])
        book[i]['examples'].append({k:v for k,v in x.items() if k!='more'})
book[36]['notes'].append('minFlow(s,t,res) 同样限制非负流值，最大/最小结果都返回每条输入边的实际流量。')
path.write_text(json.dumps(book,ensure_ascii=False,indent=2),encoding='utf-8')
print('Created',sum(map(len,examples.values())),'complete usage examples')
