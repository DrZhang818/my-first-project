#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2040/problem/B
/*
    贪心思维 || 数学
    题意:
        给定长度为n的数组, 初始值为0。
        可以进行以下两个操作
        op1:选择数组中一个数, 使其等于1
        op2:选择一个区间[l, r], 是区间全部为1
                区间需满足nums[l] == nums[r] == 1
                    并且sum(l, r) >= (len + 1) // 2
        求使得数组全部为1的合法操作序列中, cnt[op1]最小是多少
    分析题目, 得以下性质
        1.数组两端必须进行操作一
        2.尽量多地进行op2(能用就用)
        3.为了让op2效率最大, op1的间隔应尽量大
    关键思考:
        题目要求长度为n所需的最小cnt
        可以反向思考:
            当cnt等于i时, 所能满足的最大长度是多少
    从特殊到一般:
        f[1] = 1
        f[2] = 4(由性质3, 第二个操作应放置于最远的地方)
        f[3] = 10(在f[2]的基础上再加个操作1, 此时sum = 5, 再由性质3最远放到10)
        综上: 可以推导出递推式f[n + 1] = (f[n] + 1) * 2
*/

//优化空间写法
void solve1(){
    int n;
    cin >> n;
    int ans = 1, f = 1;
    while(f < n){
        f = (f + 1) * 2;
        ans++;
    }
    cout << ans << "\n";
}


//比赛时写法
vector<ll> sum(16);
void solve(){
    int n;
    cin >> n;
    cout << lower_bound(sum.begin(), sum.end(),n) - sum.begin() + 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
  
    sum[0] = 1;
    for(int i = 0; i < sum.size() - 1; i++){
        sum[i + 1] = 2 * sum[i] + 2;
    }
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}