#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2057/problem/A
/*
    贪心 || 构造
    题意:
        将排列0 ~ n*m-1 填入一个n × m的矩阵, 使得每行mex加每列mex的总和最大
        mex是第一个没有出现的自然数
        要求计算出最大值
    关键思考:
        观察矩阵, 有以下性质
        (1)不含0的行/列, mex值一定为0
        (2)有且仅有1行1列含有0
        问题转化为在这1行1列中构造最大的mex和
        当行数为n时, 行的最大mex贡献为n
        当列数为m时, 列的最大mex贡献为m
        行和列只能有一个提供最大贡献, 另一个贡献必然是1, 这是因为数字1只能出现1次
        综上, 最大贡献就是max(n, m) + 1
*/
void solve(){
    int n, m;
    cin >> n >> m;
    int mx = max(n, m);
    cout << mx + 1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
