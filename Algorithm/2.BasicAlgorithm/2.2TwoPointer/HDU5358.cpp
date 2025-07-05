#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://acm.hdu.edu.cn/showproblem.php?pid=5358
/*
    前缀和 || 二分 || 双指针
    题意:
        给定一个长度为n的数字, 要求计算出表达式
        ∑i=[1,n]∑j=[i,n] (⌊log2S(i,j)⌋+1)×(i+j) 的值
    关键思考:
        ⌊log2 x⌋+1的值就等于x的二进制长度
        前面的双重求和就是枚举每个子数组
        所以可以定义一个子数组的权值为: 子数组和的二进制长度 × 子数组左右端点下标之和
        所以题目就等价于求解每个子数组的权值之和
        思考这种问题的常见思路就是 DP || 贡献法
        由于本题涉及到整除, 因此贡献法的经典应用——整除分块就在这里派上用场了
        解决之前先思考一个问题, 为什么本题不能DP
        如果我们把这题看作一个类似计数类问题的话
        假设把二进制长度作为一个状态, 我们转移的时候需要从前面的二进制长度 + 当前数后能得到哪些新的二进制长度
        而这个状态显然非常难以维护, 并且子数组左右端点下标之和更是无解
        因此简单分析即可知道无法DP
        那么就来思考贡献法了, 很显然按照整除分块理论, 我们可以按照二进制长度进行分段计算
        由于1e5个数, 数值最大为1e5, 因此sum最大是1e10, 也就是我们只需要枚举log(sum)约为35个"段"即可
        记当前枚举到以j结尾的前缀和数组, 枚举的二进制长度为k
        那么我们需要找到和为[1 << k, 1 << k + 1)的所有子数组
        而由于a[i] >= 0, 因此前缀和数组具有单调递增的性质, 我们可以使用二分来寻找左右端点
        记录cur = s[j], L = 1 << k, R = (1 << k + 1) - 1
        那么我们要找的左端点就是第一个 >= cur - R, 右端点就是最后一个 <= cur - L
        求出来a,b之后注意转化成1-based
        这里有个细节是a = max(a, 1), b = min(b, j), 是对a,b合理范围的约束
        并且当左端点大于右端点的时候, 要及时跳过
        这两点属于防御型编程, 编程时加上可以避免出现不必要的bug
*/
void solve(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> s(n + 1);
    for(int i = 0; i < n; i++) {
        s[i + 1] = s[i] + a[i];
    }
    ll ans = 0;
    for(int j = 1; j <= n; j++) {
        ll cur = s[j];
        for(int k = 0; k <= 34; k++) {
            ll L = (k == 0 ? 0 : 1LL << k);
            ll R = (1LL << k + 1) - 1;
            ll tar_L = cur - R;
            ll tar_R = cur - L;
            ll a = lower_bound(s.begin(), s.end(), tar_L) - s.begin();
            ll b = upper_bound(s.begin(), s.end(), tar_R) - s.begin() - 1;
            a++, b++;
            a = max(a, 1LL);
            b = min(b, (ll)j);
            if(a > b) continue;
            ll sum_i = (a + b) * (b - a + 1) / 2;
            ll sum_j = j * (b - a + 1);
            ans += (sum_i + sum_j) * (k + 1);
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
    while(t--) {
        solve();
    }
    return 0;
}

