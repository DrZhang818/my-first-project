#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/108199/F
/*
    BFS || 贪心
    题意:
        给定N个数和一个长度为2N的出入栈顺序序列, 你需要构造出一个入栈填数方案
        使得每个入栈时刻的栈是唯一的(不存在两个入栈时刻的栈相同)
        出入栈的顺序用括号表示, '('表示入栈, ')'表示出栈
        注意: 每个数只能使用一次
        范围: n∈[1,1e6], a[i]∈[1,n]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 我们会发现可以按照"括号的深度"来进行分组
        "括号的深度"代表的信息就是栈中的元素数量, 显然元素数量不同的组互不影响
        这里用到一个很trick的思想: 把栈看作在一棵树上做dfs
        我们把入栈操作看作在当前分支新建一个儿子节点并访问
        把出栈操作看作返回当前节点的父亲节点
        这样每个出入栈序列都可以唯一地转化成一个n+1个节点的树形结构
        由上面的性质可知, 不同的组就对应树的不同深度
        而显然如果两个点的某个祖先节点不同, 那么得到的栈一定是不同的
        因此我们只需满足: 任意节点的直接子节点互不重复
        这就转化成了贪心进行树上染色的问题了, 我们可以用优先队列维护出现次数最多的元素
*/  
struct info {
    int v, cnt;
    friend bool operator < (const info &a, const info &b) {
        return a.cnt < b.cnt;
    }
};
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a[x]++;
    }   
    int len = s.size(); 
    s = "#" + s;
    vector<vector<int>> adj;
    vector<int> fa(n + 1);
    adj.push_back(vector<int>());
    int cur = 0;
    for(int i = 1; i <= len; i++) {
        if(s[i] == '(') {
            int nxt = adj.size();
            adj[cur].push_back(nxt);
            fa[nxt] = cur;
            cur = nxt;
            adj.push_back(vector<int>());
        } else {
            cur = fa[cur];
        }
    }
    priority_queue<info> pq;
    for(int i = 1; i <= n; i++) {
        if(a[i]) {
            pq.push({i, a[i]});
        }
    }
    queue<int> q;
    q.push(0);
    vector<int> ans(n + 1);
    while(!q.empty()) {
        int sz = q.size();
        for(int i = 0; i < sz; i++) {
            int u = q.front(); q.pop();
            vector<info> t;
            for(int k : adj[u]) {
                if(pq.empty()) { cout << "NO\n"; return ; }
                auto [v, c] = pq.top(); pq.pop();
                if(c - 1 >= 1) t.push_back({v, c - 1});
                ans[k] = v;
                q.push(k);
            }
            for(int i = 0; i < t.size(); i++) {
                pq.push(t[i]);
            }
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n]; 
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
