#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://atcoder.jp/contests/abc107/tasks/arc101_b/
/*
    二分 || 增益数组 + 前缀和 || 树状数组 or 线段树 or 归并分治
    题意:
        给定一个长度为n的数组A, 定义一个数组的中位数为数组排序后a[n / 2]的值
        定义数组B为数组A的所有子数组的中位数组成的集合
        求数组B的中位数
    关键思考:
        注: 这里为了区分, 我们用/表示上取整, //表示下取整
        本题考察对中位数的理解
        一个数组的(上取整)中位数有以下性质
        (1)数组中至少有n / 2个元素大于等于 x
        (2)中位数为满足条件(1)的x中的最大值
        当数组至少有m个元素大于x时, 一定也至少有m个元素大于x - 1
        因此具有单调性, 可以用二分法求出最大的x, 即可得到答案
        而一个数组的子数组个数为n * (n + 1) // 2
        所以二分的check就需要计算出是否有大于等于(n * (n + 1) // 2) / 2的子数组中位数大于等于x
            (n * (n + 1) // 2) / 2 等价于(n * (n + 1) // 2 + 1) // 2
        问题就转化为如何计算有多少个子数组中位数大于等于x
        我们记mid表示中位数, 由上文中位数的性质
        数组中至少有n / 2个元素 >= mid, 而mid又要 >= x
        因此这等价于数组中至少有n / 2个元素 >= x
        问题进一步转化为如何计算有多少个子数组满足至少有n / 2个元素 >= x
        这里我们不关心元素具体是多少, 只关心它是否 >= x
        那么就可以转化成增益数组来简化, 把 >= x的元素标记为1, < x的元素标记为-1
        那么至少有n / 2个元素 >= x就等价于数组和 >= 0
        从而问题进一步简化为如何计算有多少个子数组满足数组和 >= 0
        而要快速计算一个子数组的数组和, 自然想到利用前缀和来优化
        那么一个数组的数组和就表示为sum[j] - sum[i-1] >= 0
        即sum[i-1] <= sum[j]
        因此我们就可以枚举j, 统计j前面有多少个数 <= sum[j]
        这可以利用值域线段树 or 值域树状数组来解决

        换个思路, 我们可以从全局来想, 直接计算计算有多少个子数组满足数组和 >= 0
        这其实就是在计算数组的"顺序对"的个数, 自然可以归并分治经典题目"逆序对"
        可以利用分治来优雅地计算出来
*/
int s[100005];
int a[100005], b[100005], help[100005];
void solve(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
    }
    auto check = [&](int x) -> bool {
        for(int i = 0; i < n; i++) {
            s[i] = 0;
        }
        for(int i = 0; i < n; i++) {
            s[i + 1] = s[i] + (a[i] >= x ? 1 : -1);
        }
        auto merge = [&](int l, int mid, int r) -> ll {
            ll res = 0;
            for(int i = l, j = mid + 1; j <= r; j++) {
                while(i <= mid && s[i] <= s[j]) {
                    i++;
                }
                res += i - l;
            }
            int i = l, j = mid + 1, idx = 0;
            while(i <= mid && j <= r) {
                help[idx++] = (s[i] < s[j] ? s[i++] : s[j++]);
            }
            while(i <= mid) {
                help[idx++] = s[i++];
            }
            while(j <= r) {
                help[idx++] = s[j++];
            }
            for(i = l; i <= r; i++) {
                s[i] = help[i - l];
            }            
            return res;
        };
        auto dfs = [&](auto &&dfs, int l, int r) -> ll {
            if(l >= r) return 0;
            int mid = l + (r - l) / 2;
            return dfs(dfs, l, mid) + dfs(dfs, mid + 1, r) + merge(l, mid, r);
        };
        ll cnt = dfs(dfs, 0, n);
        return cnt >= ((ll)n * (n + 1) / 2 + 1) / 2;
    };
    int l = -1, r = n;
    sort(b, b + n);
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(check(b[mid])) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << b[l] << "\n";

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

