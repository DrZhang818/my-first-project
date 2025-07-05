#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2067/problem/C
/*
    数学 || 思维 || 暴力枚举 + 贪心剪枝
    题意:
        给定一个正整数n, 你可以进行以下操作:
        op: 将十进制表示只包含9的任何正整数加到n中
        要求计算出使得数字n的十进制表示中至少包含一个数字7的最小操作次数
    关键思考:
        以下所谓"s数位的9", 指的是数位1~s全部为9
        决策类问题的思考方式为: 暴力 -> DP -> 贪心, 循序渐进
        首先很容易观察出答案的上界为7
        这是因为无论什么数, 我们都可以不断加上一个远大于它的99...9
        这样最高位依次是0,1,2,...,7, 可以保证每次都能成功进位, 因此需要7次
        有了上界之后, 我们就可以在暴力过程中加入适当剪枝, 以降低时间复杂度
        答案要我们至少一个数位为7, 那么我们就可以具体地计算出每个数位成为7的最小次数, 再取min即可
        不妨从低位向高位进行枚举
        思考当前位要想变为7的方法有什么
        (1)由低位不断进位得到7
        (2)在低位进位的同时, 当前位也不断加9以得到7
        对于(1).进位的方式多种多样, 但我们可以进行贪心:
            假设当前数位是s, 那么最优策略一定是每次加上s-1数位的9
            因为99 + 99 = 198, 即对最高位的贡献最大为1
            这保证了贡献的值域是{0,1}, 即有连续性, 不会出现+2导致错过7的状况
            那么加上s-1数位的9相比加上s-2,s-3数位的9来说, 贡献1(进位)的概率显然更大
        对于(2).暴力枚举, 每次加上s数位的9即可
        枚举的过程中可以加上剪枝, 如果当前操作次数已经大于ans, 直接跳出即可
*/  
void solve(){
    ll n, temp;
    cin >> n;
    int ans = 7, cnt;
    for(ll s = 1; s <= n; s *= 10) {
        cnt = 0;
        temp = n;
        while(cnt < ans && temp / s % 10 != 7) {
            temp += s - 1;
            cnt++;
        }
        ans = min(ans, cnt);

        cnt = 0;
        temp = n;
        while(cnt < ans && temp / s % 10 != 7) {
            temp += s * 10 - 1;
            cnt++;
        }
        ans = min(ans, cnt);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}

