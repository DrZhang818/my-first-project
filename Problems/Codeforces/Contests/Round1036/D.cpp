#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


//https://codeforces.com/contest/2124/problem/D
/*
    贪心
    题意:
        给定一个长度为N的数组a和一个整数k, 你可以进行任意次以下操作:
        op: 选择一个长度大于等于k的窗口[l,r], 删除a[l:r]中的第k小元素
            如果有多个相同的第k小元素, 你可以任选其一并删除
        判断能否通过任意次操作使得数组变为回文数组
        范围: n∈[1,2e5], k∈[1,n], a[i]∈[1,n]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        首先思考题目性质, 考虑哪些数可以被删除
        考虑排序后的数组c, 并令x为c[k-1], 通过观察我们会发现以下两个性质
        (1)小于x的数一定不可删除
            这是比较显然的, 因为在整个排序后的数组中, 这些数最多是第k-2小
            那么在任何一个窗口下, 这些数都不可能成为第k小
        (2)大于x的数一定可以删除
            因为只要我们保存下来c[1]~c[k-1]这些数, 就意味着至少有一个长度为k-1的窗口
            这样只要有大于x的元素, 我们都能选出一个包含该元素的长度为k的窗口
            那么考虑从大往小删除, 记当且最大值为mx
            取一个包含mx的长度为k的窗口, 那么这个窗口内的第k小必然是mx, 因此我们可以删除它
            持续此过程直到最大的元素等于x时终止
        事实上, 我们把数组分为了三部分: 小于x、等于x、大于x
        显然, 如果一个串是回文串, 删除所有大于x的数之后得到的串仍然是回文串
        因此保留大于x的数没有任何价值, 反而添加了不必要的麻烦
        因此利用性质(2), 我们删掉所有大于x的元素得到数组b, b只包含a中小于等于x的元素
        这样目标就转化成: 利用操作使得数组b变为回文数组
        考虑从两端到中间来构造
        记录u = a[l], v = a[r]
        (1)如果u = v, 那么匹配成功
        (2)如果u != v:
            <1>如果u < x且v < x, 由性质(1), 此时必然无解
            <2>如果u = x且v < x, 那么删除u
            <3>如果u < x且v = x, 那么删除v
        注意<2><3>在删除时候必须保证窗口长度至少为k, 可以用一个变量cnt来维护剩余元素个数
*/
//优化做法
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }
    int c = 0, mn = -1;
    for(int i = 1; i <= n; i++) {
        c += cnt[i];
        if(c >= k - 1) {
            mn = i;
            break;
        }
    }
    vector<int> b{0};
    for(int i = 1; i <= n; i++) {
        if(a[i] <= mn) {
            b.push_back(a[i]);
        }
    }
    int l = 1, r = b.size() - 1;
    c -= k - 1;
    while(l < r) {
        int u = b[l], v = b[r];
        if(u == v) {
            l++;
            r--;
        } else if(!c || u < mn && v < mn) {
            cout << "NO\n";
            return;
        } else if(u == mn) {
            l++;
            c--;
        } else {
            r--;
            c--;
        }
    }
    cout << "YES\n";
}   


//赛时做法
// inline int lowbit(int o) { return o & -o; }
// class FenwickTree {
// private:
//     int n;
//     vector<ll> tr;
// public:
//     FenwickTree(int x) : n(x), tr(x + 1) {}
//     void add(int o, int x) {
//         for(; o <= n; o += lowbit(o)) {
//             tr[o] += x;
//         }
//     }
//     ll query(int o) {
//         ll res = 0;
//         for(; o > 0; o -= lowbit(o)) {
//             res += tr[o];
//         }
//         return res;
//     }
//     ll range_query(int l, int r) {
//         return query(r) - query(l - 1);
//     }
// };

// void solve() {
//     int n, k;
//     cin >> n >> k;
//     vector<int> a(n + 1);
//     for(int i = 1; i <= n; i++) {
//         cin >> a[i];
//     }
//     if(k == 1) {
//         cout << "YES\n";
//         return;
//     }
//     FenwickTree l_pre(n + 1), l_suf(n + 1), r_pre(n + 1), r_suf(n + 1);
//     for(int i = 1; i <= n; i++) {
//         l_suf.add(a[i], 1);
//         r_pre.add(a[i], 1);
//     }
//     int l = 1, r = n;
//     while(l < r) {
//         int u = a[l], v = a[r];
//         if(u == v) {
//             l_pre.add(u, 1);
//             l_suf.add(u, -1);
//             r_pre.add(v, -1);
//             r_suf.add(v, 1);
//             l++;
//             r--;
//             continue;
//         } 
//         int c1 = l_pre.range_query(1, u) + l_suf.range_query(1, u);
//         int c2 = r_pre.range_query(1, v) + r_suf.range_query(1, v);
//         if(c1 >= k && c2 >= k) {
//             if(u < v) {
//                 l_suf.add(v, -1);
//                 r_pre.add(v, -1);
//                 r--;
//             } else {
//                 l_suf.add(u, -1);
//                 r_pre.add(u, -1);
//                 l++;
//             }
//         } else if(c1 >= k) {
//             l_suf.add(u, -1);
//             r_pre.add(u, -1);
//             l++;
//         } else if(c2 >= k) {
//             l_suf.add(v, -1);
//             r_pre.add(v, -1);
//             r--;
//         } else {
//             cout << "NO\n";
//             return;
//         }
//     }
//     cout << "YES\n";
// }

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
