#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2070/problem/B
/*
    模拟 || 数学
    题意:
        给定机器人初始坐标为x(x ≠ 0), 现给定一个长度为N的移动指令, 由L和R组成
        L表示向负方向移动一格, R表示向正方向移动一格
        机器人将按照顺序依次执行指令, 每次执行一个指令耗时1秒
        每当机器人到达坐标为0的点时, 将停下后续指令, 重新从头开始执行指令
        若机器人完成了所有指令, 但未到达0点, 将停止移动
        现给定一个整数k, 要求计算出接下来的k秒内机器人会到达几次坐标为0的点
        范围: n∈[1,2e5], x∈[-n,n], k∈[n,1e18]
    关键思考:
        本题为模拟类题目, 需要灵活利用合适的算法和数据结构来维护信息并回答询问
        首先思考暴力做法, 追踪机器人的k次移动, 复杂度为O(k), 需要优化
        由于机器人每次到达0点都会重新执行, 因此从0点出发如果能再次回到0点, 那么接下来的过程
        一定就可以通过循环计算出来
        因此我们可以先计算出次到达0点所需的步数init, 这是处于循环外的步骤
        剩下k-init的步骤一定是处于循环中的
        因此问题就变成计算最小正周期T, 继续同样的步骤从0出发模拟即可


*/
void solve() { 
    ll n, x, k;
    cin >> n >> x >> k;
    string s;
    cin >> s;
    ll ans = 0, init = 0;
    for(int i = 0; i < n; i++) {
        init++;
        if(s[i] == 'L') {
            x -= 1;
        } else {
            x += 1;
        }
        if(x == 0) {
            ans += 1;
            break;
        }
    }
    if(x != 0) {
        cout << ans << "\n";
        return;
    }
    k -= init;
    ll cnt = 0;
    bool ok = false;
    for(int i = 0; i < n; i++) {
        cnt += 1;
        if(s[i] == 'L') {
            x -= 1;
        } else {
            x += 1;
        }
        if(x == 0) {
            ok = true;
            break;
        }
    }
    if(ok) {
        ans += k / cnt;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
