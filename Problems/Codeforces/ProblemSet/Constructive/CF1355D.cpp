#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/1355/problem/D/
/*
    构造 || 贪心
    题意:
        给你一个整数n和S, 你需要构造出一个长度为n且总和为S的数组
        使得存在K属于[1,S], 满足任意非空子数组的和不等于K且不等于S - K
        判断是否存在合法的数组, 若存在, 输出构造出的数组和选择的K
    关键思考:
        K和S-K这种关系就像在判断素数中的sqrt(n)和n/sqrt(n)一样, 本质上是一种对称关系, 有小的就必有
        大的, 而我们要构造的数组需要同时避开这两个数, 这样就可以借鉴三路快排的思想, 按照小中大分成三区
        我们只需要保证选取的K和S-K都落在中间区域, 而可达的子数组和落在小区和大区即可
        为什么一定要把K和S-K放在中间?
        因为如果混合放, 答案不容易控制
        当按照小中大放置时, 贪心地想, 如何让中间的尽可能容下K和S-K呢?
        ______K...S-K_____
        显然, 让前面一段尽可能小, 这样留给K选择的余地就更多
        因此可以构造1 1 1..|| n...S-n || S-(n-1)
        这样只需要n <= S-n <--> S >= 2n即可成功构造
        因此S >= 2n是可以构造的充分条件
        如何证明必要性呢?
        留空
*/
//优化解法(jiangly)
void solve1(){
    int n, s;
    cin >> n >> s;
    if(s < 2 * n){
        cout << "NO\n";
    }else{
        cout << "YES\n";
        for(int i = 0; i < n; i++){
            cout << (i < n - 1 ? 1 : s - n + 1) << " \n"[i == n - 1];
        }
        cout << n << "\n";
    }
}
//自己的写法
void solve(){
    int n, s;
    cin >> n >> s;
    int can = s - 2 * (n - 1) - 1;
    int need = 1 + (s & 1);
    cout << "can:" << can << " " << "need:" << need << "\n";
    if(can >= need){
        cout << "YES\n";
        for(int i = 0; i < n - 1; i++){
            cout << 1 << " ";
        }
        cout << s - (n - 1) << "\n";
        cout << s / 2 << "\n";
    }else{
        cout << "NO\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
