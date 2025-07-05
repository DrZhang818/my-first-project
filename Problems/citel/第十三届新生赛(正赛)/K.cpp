#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    贪心
    题意: 给定大小为2n的有序数组, 两两配对得到n个数对, 每个数对的权值为两数之和
        求一个合法配对方案, 使得n个权值的最小值最大
    关键思考:
        首先, 记2n个数的总和为sum
        那么无论是哪个方案, 总和都是固定的
        则最理想的情况就是sum/n
        因为如果按照贡献法, 如果有一个数对贡献的比这个大, 另一个数对就会小
        导致最小值更小
        进而对于离散化的数据来说, 只有最小值与最大值匹配的时候, 才更贴近这个目标
        因此最优方案就是ai与a(2n-1-i)配对
*/
void solve(){
    int n;
    cin >> n;
    vector<ll> nums(2 * n);
    for(auto &num : nums){
        cin >> num;
    }
    ll ans = LLONG_MAX;
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        ans = min(ans, nums[l++] + nums[r--]);
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}