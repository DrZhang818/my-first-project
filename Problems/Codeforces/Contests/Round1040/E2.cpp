#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2130/problem/E2
/*
    交互 || 构造 || 二分 || 状压
    题意:
        有一个长度为n的由'('和')'组成的括号序列s, 你需要通过不超过200次的查询来猜出序列s
        交互格式如下:
        ? k i_1 i_2 ... i_k: 查询由s[i_1]s[i_2]...s[i_k]拼成的字符串的合法括号子串数量
            其中, k∈[1,1000], 1 <= i_1,i_2,...,i_k <= n
            查询操作的k个索引可以重复
        ! s1s2...sn: 回答问题(不计入查询次数)
        范围: n∈[2,1000], 数据保证s中至少存在一个'('和一个')'
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于我们只能进行200次查询, 这说明平均单次查询的效率至少为5个字符
        此时E1的效率为2的分类讨论做法就不能奏效了, 我们必须找到更高明的做法
        思考下E1的做法为什么讨论极多 且效率极低
        就是因为 ((  ))  ()  )( 这四种情况难以区分, 所以我们需要大量分类讨论, 历经
        千辛万苦才得以区分开来
        但现在要求我们效率至少为5, 再想通过分类讨论解决几乎是不可能的事情
        有没有什么方法, 能让我们便于区分字符呢?
        很简单, 如果我们已知一个字符的类型, 例如知道第i个字符是')'
        那么我们想知道第j个字符是什么, 就只需要查询? 2 j i
        如果得到的答案是1, 说明s[j] = '('; 如果答案是0, 说明s[j] = ')'
        这样简洁的判别方法是很好想到的, 但它有个致命问题: 它的效率仅为1
        于是, 我们思考是否可以用这种方法同时处理多个字符呢?
        例如? 2 * k j_1 i j_2 i ... j_k i
        这样做有个明显问题, 我们不知道得到的答案是由哪些j贡献的
        为了区分, 我们有个非常高明的trick: 利用二进制状压
        我们让 <j_1,i>出现2^0次, <j_2,i>出现2^1次, ..., <j_k,i>出现2^{k-1}次
        即: ? 2 * (2^k-1) j_1 i j_2 j_2 i i ... j_k...j_k i...i
        这样, 答案的二进制表示中的第x位的状态就是j_x的状态
        然而, 这样还有个问题, 合法括号子串可以并联
        ()(())的答案是4而不是3
        这就导致答案 ≠ 各部分的答案之和, 二进制状态就失去意义了
        我们可以简单地在各部分之间穿插一个i, 这里s[i]为')', 一定能使得各部分失去并联机会
        由于询问的字符串长度不能超过1000, 因此我们必须对k加以限制
        查询k个数所需的长度是 2 * (2^k - 1) + k - 1 = 2^{k+1} + k - 3 <= 1000
        解得最大的k = 8, 也就是说我们这种方法的效率是8, 解决1000个字符需要125次
        接下来的问题是, 我们如何在75次内找到一个右括号')'呢?
        显然我们需要一个O(logn)级别的算法, 二分是我们首先要考虑的
        我们可以借鉴CF1698D的思想, 固定左端点为s[1], 查找第一个满足条件的右端点s[r]
        所谓满足条件, 就是s[1:r]内有一个合法括号子串, 即查询答案不为0
        但有种特殊情况是, 只有一个')'并且位于开头, 这样整个串怎么查答案都是0
        我们可以再次非常高明地用个小trick, 把s[1]复制一份到s[n+1], 这样就一定能够
        得到一个满足条件的右端点r了, 再判断如果r = n+1, 则令r = 1即可
*/
int query(vector<int> &a) {
    cout << "? " << a.size();
    for(int i : a) {
        cout << " " << i + 1;
    }
    cout << endl;
    int x;
    cin >> x;
    return x;
}
void solve() {
    int n;
    cin >> n;
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = lo + hi >> 1;
        vector<int> a;
        for(int i = 0; i <= mid; i++) {
            a.push_back(i % n);
        }
        if(query(a)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    int right = hi % n;
    string ans(n, '?');
    for(int i = 0; i < n; i += 8) {
        vector<int> a;
        for(int j = i; j < min(n, i + 8); j++) {
            int t = 1 << j - i;
            a.insert(a.end(), t, j);
            a.insert(a.end(), t + 1, right);
        }
        int res = query(a);
        for(int j = i; j < min(n, i + 8); j++) {
            if(res >> j - i & 1) {
                ans[j] = '(';
            } else {
                ans[j] = ')';
            }
        }
    }
    cout << "! " << ans << endl;
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
