#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://codeforces.com/contest/2050/problem/D
/*
    贪心 || 枚举
    题意: 通过邻位交换的方式, 每次代价为1, 最大化num
    有以下贪心策略:
        1.枚举右,维护左 : 要保证左(当前的i)最大
        2.如果两个右端点都能达到最大化左端点, 选择最近的右端点
*/
void solve(){
    string s;
    cin >> s;
    for(int i = 0; i < s.length() - 1; i++){
        int maxIdx = i, maxNum = s[i];
        for(int j = i + 1; j <= i + 9 && j < s.length(); j++){
            //选择最近的右端点使用 <
            //选择最远的右端点使用 <=
            if(maxNum < s[j] - (j - i)){ 
                maxNum = max(maxNum, s[j] - (j - i));
                maxIdx = j;
            }
        }
        s[maxIdx] -= (maxIdx - i);
        for(int j = maxIdx; j > i; j--){
            swap(s[j], s[j - 1]);
        }

    }
    cout << s << "\n";
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