#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://www.lanqiao.cn/problems/3491/learning/
/*
    搜索
    题意:
        定义一个数字是幸运的, 当且仅当它有偶数个数位, 并且前面一半的数位之和等于后面一半
        的数位之和, 要求计算出1~1e8之间有多少个不同的幸运数字
    关键思考:
        本题为计数类题目, 常用思考方式为: 暴力->DP||组合数学, 常用优化手段为: 前缀和、双指针、数学
        由于是填空题, 并且数据范围不大, 因此我们可以写个check函数后暴力搜索
        时间复杂度为O(nlogn), 可以很快跑出来
        check函数最方便的方式是转成字符串来处理数位
*/
bool check(int x) {
    string s = to_string(x);
    if(s.size() % 2 != 0) return false;
    int pre = 0, suf = 0;
    for(int l = 0, r = s.size() - 1; l < r; l++, r--) {
        pre += s[l] - '0';
        suf += s[r] - '0';
    }
    return pre == suf;
}
void solve() { 
    ll ans = 0; 
    for(int i = 1; i <= 100000000; i++) {
        if(check(i)) {
            ans++;
        }
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
    
