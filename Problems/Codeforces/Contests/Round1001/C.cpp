#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2062/problem/C
/*
    模拟 || 贪心思维
    题意:
        给定一个长为n的数组, 你可以对数组进行以下操作:
        op1: 翻转整个数组
        op2: 将数组变为差分数组, 即a[i] = a[i + 1] - a[i] (需满足数组长度 >= 2)
        一个数组的权值为所有元素之和
        问通过无限制的op1和op2操作后, 能够获得的最大权值是多少
    关键思考:
        op2后得到的数组权值可能为正/负
        而op1的作用是让op2得到的权值变为相反数
        因此可以保证op2得到的权值一定为正, 即把负权值取相反数
        因此贪心地想, 每次差分后得到的值取绝对值即可
        注意原数组的权值不能取绝对值, 因为原数组无法通过op1把负权值变为正权值
*/
void solve(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    ll ans = LLONG_MIN;
    int len = a.size();
    int t = len;
    while(len >= 1){
        ll sum = 0;
        for(int i = 0; i < len; i++){
            sum += a[i];
            if(i + 1 < len) a[i] = a[i + 1] - a[i];
        }
        if(len == t) ans = sum;
        else ans = max(ans, abs(sum));
        len--;
    }
    cout << ans << "\n";
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