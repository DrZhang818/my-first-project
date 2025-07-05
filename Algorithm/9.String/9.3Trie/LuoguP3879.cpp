#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.luogu.com.cn/problem/P3879
/*
    Trie
    题意:
        给定N篇文章, 每篇文章有L个单词, 总长度为|S|
        现有Q组询问, 每组询问为一个单词, 回答这个单词在哪篇文章出现过
        回答顺序按升序排列
        范围: N∈[1,1e3], |S|∈[1,5e3], 单个单词长度<=20, Q∈[1,1e4]
    关键思考:
        本题为数据结构类题目, 需要认真理解题意, 选用合适的算法和数据结构解答题目
        我们可以利用Trie来维护每个单词的信息, Trie的存储采用son数组方式构建有向图
        由于我们要有序地回答单词在哪篇文章出现过, 因此可以用一个set集合来记录
        接下来就是构建Trie的过程了, 为了节约内存, 我们使用vector来动态开点
        (1)add
            add过程就是遍历字符串, 如果发现某个字符不存在, 就动态开点, 并为其编号
            如果到达字符串结尾, 标记is_end, 并在该位置的set集合中加入文章id
        (2)query
            query的过程同样是遍历字符串, 判断一个单词是否合法的依据如下
            1.如果发现某个字符不存在对应节点(编号为0), 则不存在该单词
            2.如果某个字符遍历完, 但发现结尾字符未被标记is_end, 则不存在该单词
            否则一定是存在该单词的, 输出相应的set集合即可
*/
struct info {
    set<int> from;        
    int son[26] = {0};     
    bool is_end = false;     
};
vector<info> t;               
void add(string &s, int idx) {
    int cur = 0;
    if (t.empty()) t.push_back(info()); 
    for (int i = 0; i < s.size(); i++) {
        int ch = s[i] - 'a';
        if (t[cur].son[ch] == 0) {
            t.push_back(info());
            t[cur].son[ch] = t.size() - 1;
        }
        cur = t[cur].son[ch];
        if (i == s.size() - 1) {
            t[cur].is_end = true;
            t[cur].from.insert(idx);
        }
    }
}
void query(string &s) {
    int cur = 0;
    for (int i = 0; i < s.size(); i++) {
        int ch = s[i] - 'a';
        cur = t[cur].son[ch];
        if (cur == 0) {
            cout << "\n";
            return;
        }
    }
    if (!t[cur].is_end) {
        cout << "\n";
        return;
    }
    for (int x : t[cur].from) {
        cout << x << " ";
    }
    cout << "\n";
}
void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        while (x--) {
            string s;
            cin >> s;
            add(s, i);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        query(t);
    }
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
