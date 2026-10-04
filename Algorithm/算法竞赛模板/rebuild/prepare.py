from pathlib import Path
import json, re
ROOT=Path(__file__).resolve().parents[1]
raw=json.loads((ROOT/'rebuild/recovered.json').read_text(encoding='utf-8'))
names='dsu rollback_dsu weighted_dsu successor_dsu fenwick sparse_table segment_tree lazy_segment_tree persistent_segment_tree dynamic_segment_tree segment_tree_beats fhq_treap implicit_treap ordered_multiset li_chao convex_hull_dp cartesian_tree link_cut_tree topk dijkstra zero_one_bfs floyd topological_sort kruskal bipartite_degree_sequence incremental_apsp scc two_sat bridge_articulation edge_bcc vertex_bcc euler_trail hopcroft_karp hungarian dinic min_cost_flow lower_bound_flow difference_constraints functional_graph range_graph incremental_flow second_mst activation_events xor_mst max_weight_closure boruvka prescribed_topological_order tree_diameter tree_centroids kruskal_reconstruction_tree lca hld tree_difference virtual_tree doubling dsu_on_tree centroid_decomposition rerooting small_to_large long_chain affine_tree lis multi_knapsack digit_dp profile_dp median_transform sparse_matrix_events permutation_lcs knapsack monotone_dp interval_dp tree_knapsack sos_dp divide_conquer_dp gray_code knuth wqs bitset modint exgcd_crt combination lucas lagrange linear_sieve mobius_phi miller_rabin pollard_rho division_blocks floor_sum bsgs matrix dujiao_sieve min25_sieve divisor_updates semiring_matrix gcd_counting two_adic euler_tower euclidean_batching fft ntt fwt fps gauss xor_basis xor_system kmp z_function rolling_hash subsequence_automaton trie aho_corasick sam suffix_array minimal_rotation manacher eertree point line segment convex_hull point_in_polygon closest_pair rotating_calipers circle half_plane_intersection minkowski_sum rectangle_union binary_search mo cdq parallel_binary_search offline_connectivity sqrt_decomposition heavy_light_vertices time_blocks reverse_offline two_pointers meet_in_middle coordinate_compression sweep_line log_trick prefix_difference contribution finite_group inclusion_exclusion regret_greedy topk_states last_occurrence dyadic_blocks exchange_ordering interval_point_matching feasibility_oracle weighted_median spatial_hash l1_transform reset_segments frequency_memo reserved_coordinates modulo_pruning boolean_chain identities games'.split()
assert len(names)==len(raw),(len(names),len(raw))
OUT=ROOT/'code'; OUT.mkdir(exist_ok=True)
SRC=ROOT/'source'; SRC.mkdir(exist_ok=True)
full=set(range(37))|set(range(47,57))|{61,62}|set(range(78,87))|{87,88,89,90,91,92}|set(range(99,128))
# Incomplete problem-specific skeletons become honest technique notes, not code templates.
delete_code=set(range(40,47))|set(range(57,61))|set(range(63,78))|set(range(93,99))
book=[]
renames={
 'RollbackDSU':'UndoDSU','WeightedDSU':'WeightDSU','SuccessorDSU':'NextDSU','Fenwick':'BIT',
 'SparseTable':'ST','SegmentTree':'Seg','LazySegmentTree':'LazySeg','PersistentSegmentTree':'PST',
 'DynamicSegmentTree':'DynSeg','SegmentTreeBeats':'Beats','FHQTreap':'FHQ','ImplicitTreap':'Treap',
 'OrderedMultiset':'OrderedSet','LiChaoTree':'LiChao','ConvexHullDP':'CHT','CartesianTree':'Cartesian',
 'LinkCutTree':'LCT','ZeroOneBFS':'BFS01','BipartiteDegreeSequence':'BiDegree','IncrementalAPSP':'APSP',
 'BridgeArticulation':'Lowlink','HopcroftKarp':'HK','DifferenceConstraints':'Diff',
 'FunctionalGraph':'FuncGraph','KruskalReconstructionTree':'KRT','TreeDifference':'TreeDiff',
 'CentroidDecomposition':'Centroid','LowerBoundFlow':'BoundFlow','MinCostFlow':'MCF',
 'MaxFlowResult':'Result','SubsequenceAutomaton':'SeqAM','AhoCorasick':'AC','SuffixArray':'SA',
 'PalindromicTree':'PAM','RectangleCoverTree':'CoverSeg','FloorSumResult':'FSResult',
 'rangeQuery':'query','rangeApply':'apply','rangeChmin':'chmin','rangeSum':'sum','rangeMax':'maxi',
 'findFirst':'first','findLast':'last','insertAfter':'insert','eraseRange':'erase',
 'topologicalSort':'toposort','treeCentroids':'centroids','rotatingCalipersDiameterSquared':'diameter2',
 'closestPairSquared':'closest2','rectangleUnionArea':'rectArea','longestPalindromicSubstring':'longestPal',
 'minimalRotation':'minRotation','lagrangeInterpolate':'lagrange','feasibleCirculation':'circulation',
 'source':'s','sink':'t','previousVertex':'pv','previousEdge':'pe','rowPotential':'u',
 'columnPotential':'v','matchColumn':'match','currentRow':'row','nextColumn':'nxt',
 'minValue':'slack','matchRow':'mate','potential':'h','distance':'dis','currentDistance':'du',
 'nextDistance':'nd','componentNode':'v','component':'bel','components':'comp','nodeCount':'tot',
 'isArticulation':'cut','isBridge':'bridge','parentEdge':'pe','edgeStack':'stk',
 'blockCutTree':'tree','superSource':'S','superSink':'T','artificialEdge':'extra',
 'position':'pos','totalFlow':'flowSum','totalCost':'costSum','initialPotential':'initPot',
 'disableSuperVertices':'delSuper','isSubsequence':'check','getPolarOrder':'polarOrder',
 'pointOnLineLeft':'onLeft','pointOnSegment':'onSeg','pointOnLine':'onLine',
 'segmentIntersection':'segCross','lineIntersection':'lineCross','intersectCircleCircle':'circleCross',
 'halfPlaneIntersection':'halfPlanes','propagateCount':'count','distinctCount':'distinct',
 'ALPHABET_SIZE':'SIGMA','ALPHABET':'SIGMA','isAncestor':'isAnc','bottleneck':'bottle',
 'maxXorWithVal':'maxWith','kthXor':'kth','canBeZero':'zero','initOnce':'reduce',
 'queueMode':'spfa','rangeToRange':'rangeRange','rangeToPoint':'rangePoint','pointToRange':'pointRange',
 'feasibleCirculation':'circulation','flowSum':'flowSum'
}
def contest_style(c,i):
    if i == 62: c=c.replace('using namespace std;', 'using namespace std;\nusing i64 = long long;')
    if i == 114: c=c.replace('return min(i, j) + 1;', 'return min(i, j);')
    if i == 127: c=c.replace('if(x1 >= x2 || y1 >= y2)', 'if(x1 > x2) swap(x1, x2);\n        if(y1 > y2) swap(y1, y2);\n        if(x1 == x2 || y1 == y2)')
    if i == 6: c=c.replace('for(int p = n - 1; p;', 'for(int p = n - 1; p > 0;')
    if i==19: c=re.sub(r'\bdistance\b','du',c)
    if i in (26,27):
        p=c.index('    void dfs(int u) {');dep=0;q=p
        for q in range(c.index('{',p),len(c)):
            dep+=(c[q]=='{')-(c[q]=='}')
            if dep==0: q+=1;break
        push='components.push_back({});' if i==26 else ''
        add='components.back().push_back(v);' if i==26 else ''
        fn='''    void dfs(int s) {
        vector<pair<int, int>> cs{{s, 0}};
        dfn[s] = low[s] = ++timer; stack.push_back(s); inStack[s] = true;
        while(!cs.empty()) {
            int u = cs.back().first;
            int& i = cs.back().second;
            if(i < int(adj[u].size())) {
                int v = adj[u][i++];
                if(!dfn[v]) {
                    dfn[v] = low[v] = ++timer; stack.push_back(v); inStack[v] = true;
                    cs.push_back({v, 0});
                } else if(inStack[v]) low[u] = min(low[u], dfn[v]);
            } else {
                cs.pop_back();
                if(low[u] == dfn[u]) {
                    PUSH
                    while(true) {
                        int v = stack.back(); stack.pop_back();
                        inStack[v] = false; id[v] = count; ADD
                        if(v == u) break;
                    }
                    count++;
                }
                if(!cs.empty()) {
                    int p = cs.back().first; low[p] = min(low[p], low[u]);
                }
            }
        }
    }'''.replace('PUSH',push).replace('ADD',add)
        c=c[:p]+fn+c[q:]
    if i in (28,29,30):
        p=c.index('    void dfs(int u, int parentEdge) {');dep=0
        for q in range(c.index('{',p),len(c)):
            dep+=(c[q]=='{')-(c[q]=='}')
            if dep==0: q+=1;break
        extra='edgeStack.push_back(id);' if i==30 else ''
        back='if(dfn[v] < dfn[u]) edgeStack.push_back(id);' if i==30 else ''
        finish='''
                if(low[u] > dfn[p]) isBridge[pe] = true;
                if(cs.back()[1] && low[u] >= dfn[p]) isArticulation[p] = true;
'''
        if i==30:
            finish='''
                if(low[u] >= dfn[p]) {
                    if(cs.back()[1] || cs.back()[3] > 1) isArticulation[p] = true;
                    vector<int> v;
                    while(true) {
                        int e = edgeStack.back(); edgeStack.pop_back();
                        v.push_back(edges[e].first); v.push_back(edges[e].second);
                        if(e == pe) break;
                    }
                    sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end());
                    components.push_back(move(v));
                }
'''
        fn='''    void dfs(int s, int e) {
        vector<array<int, 4>> cs{{s, e, 0, 0}};
        dfn[s] = low[s] = ++timer;
        while(!cs.empty()) {
            int u = cs.back()[0], pe = cs.back()[1];
            int& i = cs.back()[2];
            if(i < int(adj[u].size())) {
                auto [v, id] = adj[u][i++]; if(id == pe) continue;
                if(!dfn[v]) {
                    cs.back()[3]++; EXTRA
                    dfn[v] = low[v] = ++timer; cs.push_back({v, id, 0, 0});
                } else { low[u] = min(low[u], dfn[v]); BACK }
            } else {
                int child = cs.back()[3]; cs.pop_back();
                if(!pe && child > 1) isArticulation[u] = true;
                if(cs.empty()) continue;
                int p = cs.back()[0]; low[p] = min(low[p], low[u]); FINISH
            }
        }
    }'''.replace('EXTRA',extra).replace('BACK',back).replace('FINISH',finish)
        c=c[:p]+fn+c[q:]
    if i==49:
        p=c.index('        auto find =');q=c.index('        sort(edges',p)
        c=c[:p]+'''        auto find = [&](int x) {
            int r = x; while(r != dsu[r]) r = dsu[r];
            while(x != r) {int y = dsu[x]; dsu[x] = r; x = y;}
            return r;
        };
'''+c[q:]
        c=c.replace('find(find, ', 'find(')
        p=c.index('            auto dfs =');q=c.index('            dfs(dfs, r, 0);',p)+len('            dfs(dfs, r, 0);')
        c=c[:p]+'''            vector<int> stk{r};
            while(!stk.empty()) {
                int u = stk.back(); stk.pop_back(); component[u] = r;
                for(int j = 1; j < log; j++) up[j][u] = up[j - 1][up[j - 1][u]];
                for(int v : child[u]) if(v) {
                    up[0][v] = u; depth[v] = depth[u] + 1; stk.push_back(v);
                }
            }'''+c[q:]
    # No C++20 numeric helpers. Arguments are valid positive sizes, or guarded.
    c=c.replace('int(bit_floor(unsigned(n)))','(n ? 1 << (31 - __builtin_clz((unsigned)n)) : 0)')
    c=c.replace('bit_width(static_cast<unsigned>(max(1, nodeCount)))', '(32 - __builtin_clz((unsigned)max(1, nodeCount)))')
    c=c.replace('bit_width(static_cast<unsigned>(max(1, n)))', '(32 - __builtin_clz((unsigned)max(1, n)))')
    c=c.replace('bit_width(unsigned(n))','(n ? 32 - __builtin_clz((unsigned)n) : 0)')
    c=c.replace('bit_width(unsigned(r - l + 1))','(32 - __builtin_clz((unsigned)(r - l + 1)))')
    if i==5: c=c.replace('st[0] = a;', 'if(n == 0) return;\n        st[0] = a;')
    if i==10:
        c=c.replace('x <= l && r <= y && v > tr[p].se','l == r || (x <= l && r <= y && v > tr[p].se)')
        c=c.replace('(tr[p].mx - x) * tr[p].cnt','(__int128(tr[p].mx) - x) * tr[p].cnt')
    if i==11:
        c=c.replace('optional<int> prev(int v)', 'bool prev(int v, int& res)')
        c=c.replace('optional<int> next(int v)', 'bool next(int v, int& res)')
        c=c.replace('        optional<int> res;\n','')
        c=c.replace('return res;\n    }\n    bool next','return p != 0;\n    }\n    bool next')
        pos=c.rfind('return res;');c=c[:pos]+c[pos:].replace('return res;', 'return p != 0;',1)
    if i==13:
        c=c.replace('optional<T> kth(int k) const', 'bool kth(int k, T& ans) const')
        c=c.replace('return nullopt;', 'return false;')
        c=c.replace('return tr.find_by_order(k - 1)->first;', 'ans = tr.find_by_order(k - 1)->first;\n        return true;')
    if i==36:
        c=c.replace('optional<vector<i64>> feasibleCirculation() const', 'bool feasibleCirculation(vector<i64>& ans) const')
        c=c.replace('optional<MaxFlowResult> maxFlow(int source, int sink) const', 'bool maxFlow(int source, int sink, MaxFlowResult& ans) const')
        c=c.replace('return nullopt;', 'return false;')
        c=c.replace('return recover(network);', 'ans = recover(network);\n        return true;')
        c=c.replace('return MaxFlowResult{baseFlow + extra, recover(network)};', 'ans = MaxFlowResult{baseFlow + extra, recover(network)};\n        return true;')
        start=c.index('struct LowerBoundFlow')
        p=start+re.search(r'\n\s*private:',c[start:]).start()
        fn='''
    bool minFlow(int source, int sink, MaxFlowResult& ans) const {
        assert(source != sink);
        auto network = build(true, source, sink);
        if(network.dinic.maxFlow(network.superSource, network.superSink) != network.demand) return false;
        auto& edge = network.dinic.adj[sink][network.artificialEdge];
        i64 base = inf - edge.capacity;
        network.dinic.adj[edge.to][edge.reverse].capacity = 0;
        edge.capacity = 0;
        disableSuperVertices(network);
        i64 delta = network.dinic.maxFlow(sink, source, base);
        ans = {base - delta, recover(network)};
        return true;
    }
'''
        c=c[:p]+fn+c[p:]
    if i==37:
        c=c.replace('optional<vector<i128>> solve(bool queueMode=true) const', 'bool solve(vector<i128>& d, bool queueMode=true) const')
        c=c.replace('vector<i128> d(n+1,0);', 'd.assign(n+1,0);')
        c=c.replace('return nullopt;', 'return false;').replace('return d;', 'return true;')
    if i==49:
        c=c.replace('optional<i64> bottleneck(int u, int v) const', 'bool bottleneck(int u, int v, i64& ans) const')
        c=c.replace('return nullopt;', 'return false;')
        c=c.replace('return 0;\n        }\n        return weight[lca(u, v)];', 'ans = 0;\n            return true;\n        }\n        ans = weight[lca(u, v)];\n        return true;')
    if i==51:
        c=re.sub(r'\.assign\(n,', '.assign(n + 1,',c)
        c=c.replace('return n - 1;', 'return n;').replace('return n - 1 - siz', 'return n - siz')
        p=c.index('    void work(');q=c.index('    int lca(',p)
        fn='''    void work(int root = 1) {
        vector<int> order{root}; parent[root] = 0; dep[root] = 0; cur = 1;
        for(int i = 0; i < int(order.size()); i++) {
            int u = order[i];
            if(parent[u]) adj[u].erase(find(adj[u].begin(), adj[u].end(), parent[u]));
            for(int v : adj[u]) parent[v] = u, dep[v] = dep[u] + 1, order.push_back(v);
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int u = order[i]; siz[u] = 1; int best = -1;
            for(int j = 0; j < int(adj[u].size()); j++) {
                int v = adj[u][j]; siz[u] += siz[v];
                if(best == -1 || siz[v] > siz[adj[u][best]]) best = j;
            }
            if(best >= 0) swap(adj[u][0], adj[u][best]);
        }
        vector<int> stk{root}; top[root] = root;
        while(!stk.empty()) {
            int u = stk.back(); stk.pop_back(); in[u] = cur; seq[cur++] = u;
            out[u] = in[u] + siz[u];
            for(int i = int(adj[u].size()) - 1; i >= 0; i--) {
                int v = adj[u][i]; top[v] = i == 0 ? top[u] : v; stk.push_back(v);
            }
        }
    }
'''
        c=c[:p]+fn+c[q:]
    if i==62:
        c=c.replace('int multiKnapsack(', 'i64 multiKnapsack(')
        c=c.replace('const vector<int>& v,', 'const vector<i64>& v,')
        c=c.replace('vector<vector<int>> dp(2, vector<int>', 'vector<vector<i64>> dp(2, vector<i64>')
        c=c.replace('max(0, j - m[i] * w[i])', '(j - 1LL * m[i] * w[i])')
    if i==55:
        p=c.index('    void dfsSize(');q=c.index('    template<class Add',p)
        c=c[:p]+'''    void dfsSize(int root, int p) {
        vector<int> stk{root}, order; parent[root] = p;
        while(!stk.empty()) {
            int u = stk.back(); stk.pop_back(); tin[u] = timer; euler[timer++] = u;
            order.push_back(u);
            for(int i = int(adj[u].size()) - 1; i >= 0; i--) {
                int v = adj[u][i]; if(v == parent[u]) continue;
                parent[v] = u; stk.push_back(v);
            }
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int u = order[i]; size[u] = 1;
            for(int v : adj[u]) if(v != parent[u]) {
                size[u] += size[v];
                if(!heavy[u] || size[v] > size[heavy[u]]) heavy[u] = v;
            }
            tout[u] = tin[u] + size[u] - 1;
        }
    }
'''+c[q:]
        p=c.index('    void run(');c=c[:p]+'''    void run(Add add, Answer answer) {
        if(adj.size() <= 1) return;
        vector<tuple<int, int, bool>> stk{{root, 0, false}};
        while(!stk.empty()) {
            auto [u, kind, keep] = stk.back(); stk.pop_back();
            if(kind == 0) {
                stk.push_back({u, 3, keep}); stk.push_back({u, 2, keep}); stk.push_back({u, 1, keep});
                if(heavy[u]) stk.push_back({heavy[u], 0, true});
                for(int v : adj[u]) if(v != parent[u] && v != heavy[u]) stk.push_back({v, 0, false});
            } else if(kind == 1) {
                for(int v : adj[u]) if(v != parent[u] && v != heavy[u])
                    for(int i = tin[v]; i <= tout[v]; i++) add(euler[i], 1);
                add(u, 1);
            } else if(kind == 2) answer(u);
            else if(!keep) for(int i = tin[u]; i <= tout[u]; i++) add(euler[i], -1);
        }
    }
};
'''
    if i==56:
        c=c.replace('vector<int> parent, level, size;', 'vector<int> parent, level, size, fa;')
        c=c.replace('size(adj.size()),', 'size(adj.size()), fa(adj.size()),')
        p=c.index('    int getSize(');q=c.index('    void build(',p)
        c=c[:p]+'''    int getSize(int u, int p) {
        vector<int> order{u}; fa[u] = p;
        for(int i = 0; i < int(order.size()); i++) {
            int x = order[i];
            for(int v : adj[x]) if(v != fa[x] && !blocked[v]) fa[v] = x, order.push_back(v);
        }
        for(int i = int(order.size()) - 1; i >= 0; i--) {
            int x = order[i]; size[x] = 1;
            for(int v : adj[x]) if(v != fa[x] && !blocked[v]) size[x] += size[v];
        }
        return size[u];
    }
    int getCentroid(int u, int p, int n) {
        while(true) {
            int v = 0;
            for(int x : adj[u]) if(x != p && !blocked[x] && size[x] * 2 > n) {v = x; break;}
            if(!v) return u;
            p = u; u = v;
        }
    }
'''+c[q:]
    if i==80:
        c=c.replace('if(n >= mod || n >= (i64)fac.size())\n            throw out_of_range("Combination: use Lucas or extend table");',
            'assert(n < mod && n < (i64)fac.size());')
    if i==104:
        c=c.replace('optional<u64> kthXor(u64 k)', 'bool kthXor(u64 k, u64& res)')
        c=c.replace('return nullopt;', 'return false;')
        # This only changes the kth result, leaving maxXor results intact.
        p=c.index('bool kthXor');q=c.index('void merge',p)
        sub=c[p:q].replace('u64 res = 0;', 'res = 0;').replace('return res;', 'return true;')
        c=c[:p]+sub+c[q:]
        p=c.index('u64 minXor()');q=c.index('void initOnce',p)
        sub=c[p:q].replace('u64 minXor()', 'bool minXor(u64& ans)')
        sub=sub.replace('return 0;', 'ans = 0; return true;').replace('return b[i];','ans = b[i]; return true;')
        sub=sub.replace('return numeric_limits<u64>::max();', 'return false;')
        c=c[:p]+sub+c[q:]
    if i==109:
        c=c.replace('int n, sigma;', 'int n, sigma;\n    char base;')
        c=c.replace('sigma(sigma_), nxt', 'sigma(sigma_), base(offset), nxt')
        c=c.replace("bool isSubsequence(const string& t, char offset = 'a') const", 'bool isSubsequence(const string& t) const')
        c=c.replace('cur = nxt[cur + 1][c - offset];', 'int x = c - base;\n            if(x < 0 || x >= sigma) return false;\n            cur = nxt[cur + 1][x];')
    if i==114: c=c.replace('char a =', 'unsigned char a =').replace('char b =', 'unsigned char b =')
    if i==126:
        where=c.index('    auto lowest =')
        sub='''    if(n <= 2 || m <= 2) {
        vector<Point<T>> p;
        for(auto x : a) for(auto y : b) p.push_back(x + y);
        sort(p.begin(), p.end(), [](Point<T> x, Point<T> y) {
            return x.x < y.x || (x.x == y.x && x.y < y.y);
        });
        p.erase(unique(p.begin(), p.end()), p.end());
        if(p.size() <= 2) return p;
        vector<Point<T>> h;
        for(auto x : p) {
            while(h.size() >= 2 && cross(h.back() - h[h.size()-2], x-h.back()) <= 0) h.pop_back();
            h.push_back(x);
        }
        int k = h.size();
        for(int i = int(p.size())-2; i >= 0; i--) {
            while(int(h.size()) > k && cross(h.back()-h[h.size()-2], p[i]-h.back()) <= 0) h.pop_back();
            h.push_back(p[i]);
        }
        h.pop_back(); return h;
    }
'''
        c=c[:where]+sub+c[where:]
    if i==124:
        c=c.replace('optional<Circle> circumcircle(const Point& a, const Point& b, const Point& c)',
            'bool circumcircle(const Point& a, const Point& b, const Point& c, Circle& ans)')
        c=c.replace('return nullopt;', 'return false;')
        c=c.replace('return Circle(o, dist(o, a));','ans = Circle(o, dist(o, a));\n    return true;')
    if i in (34,35,36,44):
        for a,b in {'capacity':'cap','reverse':'rev','adj':'g','level':'dep','iter':'it',
                    'Network':'Net','network':'net','lower':'lo','upper':'hi','edgeFlow':'flow',
                    'addArtificial':'addExtra','baseFlow':'base','artificial':'ex'}.items():
            c=re.sub(r'\b'+a+r'\b',b,c)
    if i in (34,36,44):
        p=c.index('    i64 dfs(');dep=0
        for q in range(c.index('{',p),len(c)):
            dep+=(c[q]=='{')-(c[q]=='}')
            if dep==0: q+=1;break
        c=c[:p]+'''    i64 dfs(int s, int t, i64 limit) {
        vector<int> st{s};
        vector<pair<int, int>> path;
        vector<i64> val{limit};
        while(!st.empty()) {
            int u = st.back();
            if(u == t) {
                i64 f = val.back();
                for(auto [v, id] : path) {
                    auto& e = g[v][id]; e.cap -= f; g[e.to][e.rev].cap += f;
                }
                return f;
            }
            int& i = it[u];
            while(i < int(g[u].size()) && (!g[u][i].cap || dep[g[u][i].to] != dep[u] + 1)) i++;
            if(i == int(g[u].size())) {
                dep[u] = -1; st.pop_back(); val.pop_back();
                if(!path.empty()) {
                    int p = path.back().first; path.pop_back(); it[p]++;
                }
            } else {
                path.push_back({u, i}); st.push_back(g[u][i].to);
                val.push_back(min(val.back(), g[u][i].cap));
            }
        }
        return 0;
    }'''+c[q:]
    # Only code identifiers are renamed; prose/example names are produced afterwards.
    c=re.sub(r'\b[A-Za-z_]\w*\b',lambda m:renames.get(m.group(),m.group()),c)
    c=c.replace('共线返回 nullopt','共线返回 false')
    if not c.lstrip().startswith('#include'): c='#include <bits/stdc++.h>\nusing namespace std;\n'+c
    assert not re.search(r'\b(optional|bit_width|bit_floor|nullopt)\b',c),(i,'unsupported API')
    return c
for i,s in enumerate(raw):
    prose=[]; code=[]
    for b in s['blocks']:
        (code if b['kind']=='code' else prose).extend(b['lines'])
    x=dict(id=i,key=names[i],title=s['title'],chapter=s['chapter'],old_page=s['old_page'],
           notes=[' '.join(prose)], examples=[], code=None, action='保留并复核', checks=[])
    c='\n'.join(code)+'\n'
    if i in full and i not in delete_code:
        # All snippets are standalone, alternative implementations, not one library.
        x['code']=names[i]+'.hpp'
        if i==3: # Deletions in ascending order can form a deep successor chain.
            c=c.replace('return x == fa[x] ? x : fa[x] = find(fa[x]);',
                'int r = x;\n        while(r != fa[r]) r = fa[r];\n        while(x != r) { int y = fa[x]; fa[x] = r; x = y; }\n        return r;')
        if i in (34,36):
            c=c.replace('int reverse = int(adj[v].size());','int reverse = int(adj[v].size()) + (u == v);')
            c=c.replace('i64 flow = 0;','assert(source != sink);\n        i64 flow = 0;',1)
        if i==35:
            c=c.replace('int vIndex = int(adj[v].size());','int vIndex = int(adj[v].size()) + (u == v);')
            c=c.replace('vector<i64> potential = initialPotential(source);','assert(source != sink);\n        vector<i64> potential = initialPotential(source);')
        if i==27: # Permit solve, add clauses, solve again.
            c=c.replace('bool solve() {','bool solve() {\n        timer = count = 0; stack.clear();\n        fill(dfn.begin(), dfn.end(), 0);\n        fill(low.begin(), low.end(), 0);\n        fill(inStack.begin(), inStack.end(), false);')
        if i==36:
            c=c.replace('int id = int(edges.size());\n        edges.push_back({from, to, lower, upper});',
                'assert(0 <= lower && lower <= upper);\n        int id = int(edges.size());\n        edges.push_back({from, to, lower, upper});')
        if i==54:
            c=c.replace('value[0] = weight;','value[0] = weight;\n        for(int j = 0; j < log; j++) value[j][0] = identity;')
        if i==78:
            c=c.replace('x += rhs.x;\n        if(x >= MOD)',
                'i64 sum = i64(x) + rhs.x;\n        x = int(sum >= MOD ? sum - MOD : sum);\n        if(false)')
            c=c.replace('        if(false) {\n            x -= MOD;\n        }\n','')
        if i==79:
            c=c.replace('i128 r = (i128(r1)',
                'if(lcm > numeric_limits<i64>::max()) throw overflow_error("CRT modulus");\n    i128 r = (i128(r1)')
        if i==80:
            c=c.replace('if(n >= mod) {\n            return 0;\n        }',
                'if(n >= mod || n >= (i64)fac.size())\n            throw out_of_range("Combination: use Lucas or extend table");')
        if i==91:
            c=c.replace('pair<i64, i64> get(i64 n) {','pair<i64, i64> get(i64 n) {\n        if(n <= 0) return {0, 0};')
            c=c.replace('unordered_map<i64, pair<i64, i64>>','unordered_map<i64, pair<i128, i64>>')
            c=c.replace('pair<i64, i64> get(', 'pair<i128, i64> get(')
            c=c.replace('{i64(sumPhi), sumMu}', '{sumPhi, sumMu}')
            c=c.replace('i128(n) * (n + 1)', 'i128(n) * (i128(n) + 1)')
        if i==82: c=c.replace('int res = 0;', 'i64 res = 0;')
        if i==92:
            c=c.replace('while(pe * p <= x)', 'while(pe <= x / p)')
            c=c.replace('sq = int(sqrt((long double)n));','assert(n >= 1 && mod > 3);\n        sq = int(sqrt((long double)n));\n        while(1LL * (sq + 1) * (sq + 1) <= n) ++sq;\n        while(1LL * sq * sq > n) --sq;')
        if i==101:
            for f in ('convOr','convAnd','convXor'):
                c=c.replace('vector<int> '+f+'(vector<int> a, vector<int> b) {',
                    'vector<int> '+f+'(vector<int> a, vector<int> b) {\n    if(a.empty() || b.empty()) return {};\n    for(int& x : a) x = (x % P + P) % P;\n    for(int& x : b) x = (x % P + P) % P;')
        if i==102:
            c=c.replace('while(n < min(resSize, limit))', 'while(n < resSize)')
        if i==103:
            c=c.replace('pivotCol.assign(m + 1, 0);', 'pivotCol.assign(m + 1, 0);\n    if(n <= 0) return 0;')
            c=c.replace('db eps = EPS)', 'db eps = EPS, int variables = -1)')
            c=c.replace('int mod, vector<int>& pivotCol)', 'int mod, vector<int>& pivotCol, int variables = -1)')
            c=c.replace('gaussXor(vector<vector<int>>& a, vector<int>& pivotCol)', 'gaussXor(vector<vector<int>>& a, vector<int>& pivotCol, int variables = -1)')
            c=c.replace('int limit = (m == n + 1 ? m - 1 : m);','int limit = variables < 0 ? m - 1 : variables;\n    assert(0 <= limit && limit <= m);')
        if i==104:
            c=c.replace('u64 kthXor(u64 k) {','optional<u64> kthXor(u64 k) {\n        if(k == 0) return nullopt;')
            c=c.replace('return numeric_limits<u64>::max();\n        }\n        u64 res', 'return nullopt;\n        }\n        u64 res')
        if i==107: c=c.replace('z[1] = n;', 'if(n == 0) return z;\n    z[1] = n;')
        if i==108: c=c.replace('u64(t[i])', 'u64((unsigned char)t[i]) + 1')
        if i==115:
            c=c.replace('string t = "$#";', 'vector<int> t = {257, 256};')
            c=c.replace('t += c;\n        t += \'#\';', 't.push_back((unsigned char)c);\n        t.push_back(256);')
            c=c.replace("t += '&';", 't.push_back(258);')
        if i==116:
            c=c.replace('int last;', 'int last;\n    bool propagated = false;')
            c=c.replace('void propagateCount() {','void propagateCount() {\n        if(propagated) return;\n        propagated = true;')
            c=c.replace('int extend(int pos) {', 'int extend(int pos) {\n        assert(!propagated);')
        # Geometry predicates are exact for integral input; widening precedes products.
        if i in (117,118,119,120,121,123,125,126):
            c=c.replace('using db = double;', 'using db = long double;')
            c=c.replace('T dot(', 'auto dot(').replace('T cross(', 'auto cross(').replace('T square(', 'auto square(')
            c=c.replace('return a.x * b.x + a.y * b.y;',
                'using W = conditional_t<is_integral_v<T>, __int128_t, long double>;\n    return W(a.x) * b.x + W(a.y) * b.y;')
            c=c.replace('return a.x * b.y - a.y * b.x;',
                'using W = conditional_t<is_integral_v<T>, __int128_t, long double>;\n    return W(a.x) * b.y - W(a.y) * b.x;')
            c=re.sub(r'\bT (c|cp1|cp2|cp3|cp4) = cross',r'auto \1 = cross',c)
            c=c.replace('db(abs(cross(', 'db(fabsl((long double)cross(')
            if i==120:
                c=c.replace('int n = int(p.size());\n    if(n <= 2)',
                    'sort(p.begin(), p.end());\n    p.erase(unique(p.begin(), p.end()), p.end());\n    int n = int(p.size());\n    if(n <= 2)')
            if i==123:
                c=c.replace('T dist2(', 'auto dist2(')
                c=c.replace('return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);',
                    'using W = conditional_t<is_integral_v<T>, __int128_t, long double>;\n    W dx = W(a.x) - b.x, dy = W(a.y) - b.y;\n    return dx * dx + dy * dy;')
                c=c.replace('T rotatingCalipersDiameterSquared(', 'auto rotatingCalipersDiameterSquared(')
                c=c.replace('if(n < 2) {\n        return 0;\n    }\n    T best = 0;',
                    'using W = decltype(dist2(Point<T>(), Point<T>()));\n    if(n < 2) return W(0);\n    W best = 0;')
        if i==124: c=c.replace('using db = double;', 'using db = long double;')
        if i==127:
            c=c.replace('vector<i64> len;', 'vector<__int128> len;')
            c=c.replace('ys[r + 1] - ys[l]', '(__int128)ys[r + 1] - ys[l]')
            c=c.replace('i64 coveredLength()', '__int128 coveredLength()')
            c=c.replace('(events[i].x - last)', '((__int128)events[i].x - last)')
        override=ROOT/'rebuild/additions'/x['code']
        if override.exists():
            c=override.read_text(encoding='utf-8'); x['action']='重写完整实现与说明'
        c=contest_style(c,i)
        (OUT/x['code']).write_text('#pragma once\n'+c,encoding='utf-8')
    elif code:
        x['action']='删掉未闭合代码，改为条件与公式速查'
    book.append(x)
for i in (37,38,39,41,43,44,45,56,91,92,112,122,125,126,129,130,131,132):
    path=ROOT/'rebuild/additions'/f'{names[i]}.hpp'
    if path.exists():
        book[i]['code']=path.name;book[i]['action']='重写完整实现与说明'
        (OUT/path.name).write_text('#pragma once\n'+contest_style(path.read_text(encoding='utf-8'),i),encoding='utf-8')
(SRC/'handbook.json').write_text(json.dumps(book,ensure_ascii=False,indent=2),encoding='utf-8')
print('Prepared',len(book),'entries;',sum(bool(x['code']) for x in book),'code files')
