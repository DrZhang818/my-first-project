#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1698/problem/D
/*
    二分 || 构造 || 交互
    题意:
        有一个长度为N的排列, N为奇数, 对其中n - 1个元进行两两配对并交换位置, 求剩下的1个元素
        你可以进行以下交互:
        "? l r": 查询[l,r]内元素, 系统会按照升序排列返回[l,r]内的元素
        "! x": 回答 x 为剩下的一个元素
        查询操作最多进行15次
        范围: n∈[3,1e4)∧n为奇数
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        由于查询次数很少, 不难想到我们需要利用二分的方式来查询不动点
        观察操作的性质, 我们会有以下结论:
        查询[l,r]内的元素, 如果满足l <= x <= r的元素的个数是奇数, 那么[l,r]内一定有不动点
        反之一定没有不动点
        下面给出证明:
        取a在[l,r]内的元素x = a[i]
        (1)如果x是不动点, 那么对l <= x <= r的贡献是1
        (2)如果x进行了交换, 设交换元素为y:
            如果l <= y <= r, 那么y也会落在[l,r]内, 且x,y都会做贡献, 贡献为2
            如果y不在[l,r]内, 那么y不会做贡献, 且x也不会做贡献, 贡献为0
        综上, [l,r]内x∈[l,r]的个数是奇数当且仅当[l,r]内存在不动点
        那么我们就可以利用二分来找不动点了

*/
void query(int l, int r) {
    cout << "? " << l << " " << r << endl;
}
void solve() {
    int n;
    cin >> n;
    int l = 1, r = n;
    while(l < r) {
        int mid = l + r >> 1;
        query(1, mid);
        int cnt = 0;
        for(int i = 1; i <= mid; i++) {
            int x;
            cin >> x;
            cnt += (x <= mid);
        }
        if(cnt & 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    cout << "! " << l << endl;    
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
