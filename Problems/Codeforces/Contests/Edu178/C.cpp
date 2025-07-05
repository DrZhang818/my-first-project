#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2104/problem/C
/*
    博弈论 || 贪心
    题意:
        Alice和Bob正在玩游戏, 他们共有N张牌, 编号为1~N
        规定编号i的牌能战胜编号j的牌, 当且仅当i > j
        其中一个特例为: 编号为1的牌能够战胜编号为n的牌
        每回合依次发生以下事件:
        (1)Alice选出一张牌, 牌面朝上放在桌面上
        (2)Bob看到Alice的牌后, 从自己的牌中选一张牌, 牌面朝上放在桌面上
        如果Alice的牌能战胜Bob的牌, 则Alice拿走两张牌; 反之Bob拿走两张牌
        拿走的牌后续回合可以继续出牌
        当回合开始时, 如果一方没有手牌, 则判负
        Alice和Bob都聪明绝顶, 会按照各自的最优策略出牌, 请你判断谁会赢得这场游戏
        输入时给定一个只含'A'||'B'的字符串, 表示起始时第i张牌在Alice||Bob手中
        范围: N∈[2,50]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于有战胜后取回这一操作, 这意味着每回合能战胜就战胜一定是不劣的(无损失)
        因此贪心策略十分明确, 每个人都要能赢就赢
        从Bob视角看, 要满足Alice无论出什么都能战胜, 只要有了这一条件, Bob一定会赢
        否则如果有一张牌Alice出了Bob无法战胜, 那么Alice可以一直出这张牌, Bob一定会输
        所以我们只需要讨论Alice是否有张牌能一直赢Bob就可以了
        考虑编号n这张牌
        (1)如果Bob持有这张牌, 意味着[2,n-1]都会被Bob战胜
           此时考虑编号1这张牌, 如果归Bob所有, 那么Alice必输
           如果归Alice所有, 那么Bob必须在[2,n-1]中有一张牌, 否则Alice一直出1可赢
           综上, 两种情况可合并为Bob在[1,n-1]中至少有一张牌
        (2)如果Alice持有这张牌, 意味着[2,n-1]都会被Alice战胜
           此时考虑编号1这张牌, 如果归Alice所有, 那么Alice必胜
           如果归Bob所有, 那么Alice必须有编号为n-1这张牌
           否则Alice出n会被1克制, 出其余牌会被n-1克制
    有趣的测试:
        经过测试, Alice的获胜概率为37%, 是一个先手劣势游戏, 符合直觉
*/
void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    if(s[n] == 'B') {
        int cnt = 0;
        for(int i = 1; i <= n; i++) cnt += s[i] == 'B';
        if(cnt > 1) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    } else {
        if(s[1] == 'A' || s[n - 1] == 'A') {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
}

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
