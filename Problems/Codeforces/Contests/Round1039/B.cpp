#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/2128/problem/B
/*
    构造
    题意:
        定义一个大小为n的数组是坏的, 当且仅当存在1 <= i <= n - 4满足以下任一条件:
        (1)a[i] < a[i + 1] < a[i + 2] < a[i + 3] < a[i + 4]
        (2)a[i] > a[i + 1] > a[i + 2] > a[i + 3] > a[i + 4]
        若数组不是坏的, 则称其是好的
        给定一个1~N的排列p, 你需要通过N次以下操作构造一个长度为N的数组q, 并使得数组是好的
        op: 移除当前数组p的最左端或最右端元素, 将其添加到数组q的末尾
        输出一种合法方案, 由L和R两种字符构成, s[i]='L'表示第i次操作移除p的最左端元素, s[i]='R'表示
        第i次操作移除p的最右端元素
        可以证明在给定约束下一定有解
        范围: N∈[5,1e5]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于排列中元素互不相同, 因此任意两个元素必定有大小关系
        我们尝试能否让数组一增一减, 这样显然能够满足要求
        我们用tag = 1表示当前要选a[l]和a[r]中较小的数, tag = 0表示要选较大的数
        不妨设当前tag = 1, a[l] < a[r]
        那么我们这轮选择a[l]
        下一轮我们tag = 0, 并从a[l + 1]和a[r]中选择较大的数
        而由于a[r] > a[l], 因此我们总能让选出来的数大于a[l], 因此数组在这两个数间递增
        那么再下一轮tag = 1, 我们要选出较小的数, 由于上一轮选的是较大的一个, 因此这一轮必然能选出一个
        比它小的数, 从而数组递减
        我们这样就保证了
        (1)数组当前轮选较小的数, 下一轮必然能选出一个大于该数的数
        (2)数组当前轮选较大的数, 下一轮必然能选出一个小于该数的数
        因此我们构造出了强化命题, 即满足一增一减, 当然也符合题目的要求
*/
void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int tag1 = 1;
    int l = 1, r = n;
    while(l <= r) {
        int tag2 = a[l] < a[r];
        if(tag1 ^ tag2) {
            cout << "R";
            r--;
        } else {
            cout << "L";
            l++;
        }
        tag1 ^= 1;
    }
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
