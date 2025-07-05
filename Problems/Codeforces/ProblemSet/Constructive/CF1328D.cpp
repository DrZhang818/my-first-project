#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1328/problem/D
/*
    构造 || 贪心
    题意:
        给定一个长度为N的循环数组a, 你需要构造数组b, 满足a[i]!=a[i+1]则b[i]!=b[i+1]
        问数组b最少出现几种不同的值, 记这个最小值为k, 构造出一个长度为N的数组b, 满足b[i]∈[1,k]
        范围: n∈[3,2e5], a[i]∈[1,2e5]
    关键思考:
        本题构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先观察题目性质, 当数组a的所有元素相同时, 显然最优解是k=1, b数组是全1数组
        当数组a出现不同元素时, 必然有k >= 2
        下面我们思考: 当k = 2时能够满足什么样的a数组呢?
        假设没有循环这条限制, k = 2已经能够解决所有情况了, 因为1 2 1 2...就是一个合法解
        但循环的限制就使得首尾衔接的时候会出问题, 我们仍然从特殊情况进行思考:
        (1)当N为偶数时, 此时1 2 1 2...必然是合法解, 因为首尾必然不相同
        (2)当N为奇数时, 这样的构造就会出问题了, 但我们有个取巧的方法, 就是看能不能转化成N为偶数的情况
            <1>如果数组中存在一对相邻相同的数, 那么我们可以让这两位填的数相同, 相当于做了一个缩点
               这样我们就把数组的长度缩为了偶数情况, 可以按照(1)的方法解决
            <2>如果任意一对相邻的都不相同, 但是a[1]和a[n]相同, 那么1 2 1 2 ... 1这样的构造
               仍然是合法的
            <3>如果在<2>的基础上a[1]和a[n]也不相同, 那么说明在循环意义上也没有一对相邻相同的数
               这样的情况下k = 2显然是无法满足的
               证明: 假设k = 2可以满足, 那么b[i]∈{1,2}, 不妨设b[1] = 1, 由于a[i] != a[i+1]恒成立
                    故b[i] != b[i+1]恒成立, 则b必为1 2 1 2 ... 1的形式
                    由于b[1] = b[n]但a[1] != a[n], 故与b的定义矛盾
               因此k >= 3
               当k = 3时一定是可满足的, 我们只需要把b[n]更换为3就得到了合法的b数组
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1), ans(n + 1, 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int mx = 1;
    bool ok = n % 2 == 0, sel = 0;
    for(int i = 2; i <= n; i++) {
        if(a[i] == a[i - 1]) {
            ok = true;
            sel = n % 2 == 1;
        } else {
            mx = 2;
        }
    }
    if(mx != 1) {
        if(ok) {
            for(int i = 1; i <= n; i++) {
                if(a[i] == a[i - 1] && sel) {
                    ans[i] = ans[i - 1];
                    sel = false;
                } else {
                    ans[i] += ans[i - 1] == 1;
                }
            }
        } else {
            for(int i = 1; i <= n; i++) {
                ans[i] += i & 1;
            }
            if(ans[1] == ans[n] && a[1] != a[n]) {
                ans[n] = 3;
                mx = 3;
            }
        }
    }
    cout << mx << "\n";
    for(int i = 1; i <= n; i++) {
        cout << ans[i] << " \n"[i == n];
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
