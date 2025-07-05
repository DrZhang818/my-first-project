#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://icpc.bjtu.edu.cn/contest/1383/problem/B
/*
    数学 || 贪心思维
    题意:
        给定两个区间, 求出区间交集长度
    关键思考:
        考虑固定其中一个区间
        此时与另一个区间做交集运算
        那么左端点一定不会变小, 右端点一定不会变大
        因此交集端点可以直接利用max和min来计算
        最后长度跟0取max即可
*/
void solve(){
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    int l = max(l1, l2);
    int r = min(r1, r2);
    cout << max(0, r - l) << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);


    solve();
    return 0;
}