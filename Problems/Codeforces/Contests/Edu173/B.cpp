#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2043/problem/B
/*
    数学
    本题是纯数学题, 没有什么好讲的
    关键思考:
        7的情况怎么判断?
        注意到1001 == 7 * 11 * 13
        那么    1001
               10010
            + 100100
            ——————————
              111111
        这正好是6个1的情况, 即n = 3, d = 1
    let A = 111111
    那么n = 3, d = 2,3,4,...9都可以表示为A的倍数, 自然也是成立
    当n > 3时, 如n = 4
        此时可以以6个1为一组分成若干组, 每组都是7的倍数, 自然成立
    由此能够推出n >= 3时一定成立
    当n < 3时
        仍然记A = n!个1
        可以证明A不是7的倍数
        那么只有d = 7时才成立
*/
//数学解法
void solve1(){
    ll n, d;
    cin >> n >> d;
    cout << 1 << " ";
    if(n >= 3 || d % 3 == 0){
        cout << 3 << " ";
    }
    if(d == 5){
        cout << 5 << " ";
    }
    if(n >= 3 || d == 7){
        cout << 7 << " ";
    }
    if(n >= 6 || n >= 3 && d % 3 == 0 || d == 9){
        cout << 9 << " ";
    }
    cout << "\n";
}
//模拟做法
void solve2(){
    int n, d;
    cin >> n >> d;
    n = min(n, 6);
    int m = 1;
    for(int i = 1; i <= n; i++){
        m *= i;
    }
    for(int v = 1; v <= 9; v += 2){
        int x = 0;
        for(int i = 0; i < m; i++){
            x = (10 * x + d) % v;
        }
        if(x == 0){
            cout << v << " ";
        }
    }
    cout << "\n";
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve2();
    }
    return 0;    
}
