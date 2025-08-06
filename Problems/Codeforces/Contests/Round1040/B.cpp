#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2130/problem/B
/*
    构造 || 数论
    题意:
        给定一个长度为N的数组a和一个整数s, 数组a由{0,1,2}组成, 且0,1,2至少各有一个
        Alice的任务是选择一个满足以下条件的合法操作序列p:
            设Alice找到的序列长度为m
            (1)p[1] = 1, p[m] = N
            (2)∀ 1 <= i <= m, 满足1 <= p[i] <= N
            (3)∀ 1 <= i <  m, 满足|p[i] - p[i + 1]| = 1
            (4)∑a[p[i]] = s, i∈[1,m]
        Bob的任务是通过重新排列数组a, 使得Alice找不到任何一个合法操作序列
        请你判断Bob能否达成目标? 如果可以请你替Bob找到重排后的数组, 如果不可以输出-1
        范围: N∈[3,50], s∈[0,1000]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先不难观察到两个简单情况:
        设数组元素总和为sum
        (1)如果sum == s:
            此时无论怎么调整, Alice都可以从头到尾每个数只选一次, 这样必然能得到s
            因此答案为-1
        (2)如果sum > s:
            由于Alice不可能获得比sum更小的得分, 因此无需调整
        当sum < s时, 我们令二者差值s - sum = d
        显然我们不能让0和1挨在一起, 否则Alice在这01之间重复移动d次就能得到s了
        而题目又保证0,1,2至少各有一个
        因此0和2, 1和2必然会相邻
        循环一次02, 我们会收获得分2
        循环一次03, 我们会收获得分3
        根据裴蜀定理, 所有大于2 * 3 - 2 - 3 = 1的数都可以被表示, 1不可以被表示
        因此, d >= 2是必定无解的
        d = 1时, 我们可以把数组重排为0...02...21...1这样的形式, 保证了无法得到1
*/
void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n + 1);
    int sum = 0;
    int c0 = 0, c1 = 0, c2 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        c0 += a[i] == 0;
        c1 += a[i] == 1;
        c2 += a[i] == 2;        
    }
    s -= sum;
    if(s == 0 || s > 1) {
        cout << -1 << "\n";
        return;
    }
    for(int i = 0; i < c0; i++) cout << 0 << " ";
    for(int i = 0; i < c2; i++) cout << 2 << " ";
    for(int i = 0; i < c1; i++) cout << 1 << " ";
    cout << "\n";
}   

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
