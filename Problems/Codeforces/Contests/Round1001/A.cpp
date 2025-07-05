#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2062/problem/A
/*
    贪心 
    题意:
        给定一个二进制字符串, 你可以进行以下操作
        op: 选定一个合法子串, 并反转每个位置   一个字符串是合法的, 当且仅当相邻位置字符不相等
        问使得字符串变为全0字符串所需的最小操作次数
    关键思考:
        由于合法子串必须是01交替出现的形式, 因此设选择了长度为k的子串, 他的实际贡献为
        子串中1的个数 - 0的个数, 而交替出现保证了贡献∈{-1,0,1}
        因此选择长度为k的子串与选择单个字符1作为子串相比, 一定是不优的
        因为选择单个字符1作为子串的贡献一定是1
        所以最优策略就是每个1单独反转, 答案为count('1')
*/
void solve(){
    string s;
    cin >> s;
    int ans = count(s.begin(), s.end(), '1');
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