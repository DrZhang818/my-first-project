#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2128/problem/C
/*
    构造 || 贪心
    题意:
        给定一个全0数组a和一个目标数组b, 长度均为N, 判断能否通过以下操作使得a转化为b:
        op: 选择一个大于min(a)的整数x, 定义i为满足a[i] < x的最小索引, 将a[i]增加x
        范围: N∈[2,2e5], b[i]∈[1,1e9]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        贪心的想, 我们在操作位置i时, 希望min(a[1]~a[i-1])越大越好, a[i]越小越好
        这样我们的操作空间能够最大化
        操作空间为: x ∈ [a[i] + 1, min(a[1] ~ a[i-1])]
        因此, 为了让min(a[1] ~ a[i-1])最大化, 我们必然要从左到右依次构造
        我们记mn = min(a[1] ~ a[i-1])
        则x ∈ [a[i] + 1, mn]
        考虑a[i]能够变成哪些数, 等价于求解通过若干次操作a[i]能够达到的最大值
        考虑最后一次操作, 此次操作使得a[i]从 < mn变为 >= mn, 从而操作终止
        显然, 这次操作能带来的最大贡献就是x = mn
        对于a[i] < mn的状态, a[i]能达到的最大值是mn - 1
        我们发现, 这两个最大值可以共同取得, 因此a[i]能达到的最大值是2 * mn - 1
        构造方法也很简单, 第一次取x = mn-1, 第二次取x = mn
        因此只需维护mn, 判断b[i] 是否 <= mn即可
        问: 为什么[0 ~ 2 * mn - 1]都是可达的?
        答: 我们给出构造性方法, 原构造是mn - 1和mn
            如果想让结果变小, 只需先把mn - 1调小, 不够再把mn调小, 由于步进最小为1
            因此[0 ~ 2 * mn - 1]都可达
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }    
    int mn = a[1];
    for(int i = 2; i <= n; i++) {
        if(a[i] > 2 * mn - 1) {
            cout << "NO\n";
            return;
        }
        mn = min(mn, a[i]);
    }
    cout << "YES\n";
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
