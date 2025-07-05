#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/1316/problem/A
/*
    贪心
    题意:
        数组A包含N个学生的成绩, 试卷满分为M, 你是第一个学生, 你希望通过调整以最大化自己的成绩
        调整规则如下:
        (1)所有学生分数都是整数
        (2)0 <= A[i] <= M
        (3)全班平均分不变 
    关键思考:
        本题为决策类题目, 常用思考方式为: 暴力->DP||贪心, 常用优化手段为: 二分、前缀和、双指针、数据结构
        总平均分不变意味着∑A[i]不变, 而每个学生分数不能为负, 因此第一个学生分数最大为sum
        同时分数不能超过M
        因此答案为min(m, sum)

*/
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    cout << min(m, sum) << "\n";
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
    
