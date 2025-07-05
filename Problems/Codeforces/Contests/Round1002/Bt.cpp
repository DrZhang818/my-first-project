#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://codeforces.com/contest/2059/problem/B
/*
    贪心————最优划分
    题意:
        给定一个长度为n的数组和一个偶整数k, 你需要将数组拆分成k个非空子数组
        然后将所有具有偶数索引的子数组连接成一个数组B, 0会被加到数组B的末尾
        定义数组B的权值为B[i] != i的最小索引(i从1开始), 求B的最小权值
    关键思考:
        此类贪心题目一定要遵循从简单到复杂的方向进行思考
        划分子数组问题方案数为C[n - 1][k - 1] 
        (1)考虑特殊情况n == k, 此时划分方法唯一确定
            这时候就等价于"偶数位"第一个出现a[i] != i的索引
        (2)对于一般情况, 贪心的想, 首先要在2->n中找出第一个不为1的数
            a.如果这个数的索引在[2,n-k+2]内, 答案一定是1
              因为索引[2,n-k+2]就是数组B的首位可能的位置
            b.如果这个数的索引在(n-k+2,n]内, 答案一定是2
              因为这意味着[1,n-k+2]全部为1
              而由于此时n != k, 即n > k
              所以n-k+2-1+1 == n-k+2 > 2
              即至少有3个1, 那么只需要在第一个1后面切1刀, 后面的1组在一起
              也就是至少有2个1在第一段偶数段, 这样B[2] == 2 != 1, 因此答案一定是2
*/

//赛后写法
void solve1() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int idx = 1;
    if(n == k){
        for(int i = 1; i < n; i += 2) {
            if(a[i] != idx) {
                break;
            }
            idx++;
        }
        cout << idx << "\n";
    }
    else{
        int idx = n + 1;
        for(int i = 2; i <= n; i++){
            if(a[i - 1] != 1){
                idx = i;
                break;
            }
        }
        if(2 <= idx && idx <= n - k + 2) {
            cout << "1\n";
        }
        else{
            cout << "2\n";
        }
    }
}
//比赛时写法
const int inf = 1e9;
void solve(){
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int cnt = 0;
    k -= 1;
    for(int i = 1; i < n - k; i++){
        if(a[i] != 1){
            cout << 1 << "\n";
            return;
        }
    }
    cnt = n - k;
    if(a[n - k] != 1) {
        cout << 1 << "\n";
        return;
    }
    if(cnt >= 2) {
        cout << 2 << "\n";
        return ;
    }
    int ans = 1;
    if(cnt == 1) {
        for(int i = 1; i < n; i += 2){
            if(a[i] != ans){
                cout << ans << "\n";
                return;
            }else{
                ans++;
            }
        }
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
        solve1();
    }
    return 0;
}

