#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P2730
/*
    BFS || 最短路
    题意:
        给定一个2×4的矩阵, 初始时顺时针填充了数字1~8
        你有三种类型的操作:
        opA: 交换上下两行
        opB: 讲最右边一列插入最左边
        opC: 中央四格作顺时针旋转
        给定一个长度为8的数组表示目标状态, 计算转化成目标状态所需的最小操作次数
        并输出字典序最小的合法解
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        首先观察题目性质, 给定了起始状态和结束状态, 求两个状态最小转化次数
        这可以建模为图论问题, 把状态看作一个节点, 把当前状态与可直达状态连边
        问题就变成求解从起始状态到结束状态的最短路问题
        由于三种操作代价相等, 因此考虑使用普通BFS来求解最短路
        这个图的特别之处在于, 一个状态可能对应很多个节点, 这时我们只处理最早出现的那一个即可
        去重后的实际节点数为O(8!), 可以通过
        由于要输出路径, 因此我们可以使用umap来记录每种状态对应的操作序列
        umap同时起到了去重 + 记录路径的作用
*/
void solve() { 
    int n = 8;
    string en;
    for(int i = 1; i <= 8; i++) {
        char c;
        cin >> c;
        en += c;
    }
    string st = "12345678";
    queue<string> q;
    q.push(st);
    unordered_map<string,string> mp;
    mp[st] = "";
    auto opA = [&](string &s) -> string {
        string t = s;
        reverse(t.begin(), t.end());
        return t;
    };
    auto opB = [&](string &s) -> string {
        string t;
        t += s[3];
        for(int i = 0; i < 3; i++) t += s[i];
        for(int i = 5; i < 8; i++) t += s[i];
        t += s[4];
        return t;
    };
    auto opC = [&](string &s) -> string {
        string t = s;
        t[1] = s[6], t[2] = s[1], t[5] = s[2], t[6] = s[5];
        return t;
    };
    string ans;
    while(!q.empty()) {
        string u = q.front(); q.pop();
        if(u == en) { ans = mp[u]; break; }
        string va = opA(u), vb = opB(u), vc = opC(u);
        if(mp.find(va) == mp.end()) mp[va] = mp[u] + "A", q.push(va);
        if(mp.find(vb) == mp.end()) mp[vb] = mp[u] + "B", q.push(vb);
        if(mp.find(vc) == mp.end()) mp[vc] = mp[u] + "C", q.push(vc);
    }
    cout << (int)ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if(i % 60 == 59 || i == ans.size() - 1) cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
