#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/repeated-substring-pattern/description/
/*
    KMP || 思维
    题意: 给定一个字符串, 判断字符串能否由一个字串重复多次构成
    关键思考:
        设最小重复子串为s'
        那么s可以写为s's's's'...(假设为k个)
        考虑计算字符串的lps数组, 假如s具有性质, 那么lps[n-1]的长度一定是(k-1)个s'
        而字符串的长度是k个s'的长度
        因此具有性质的字符串一定满足 n % (n-lps[n-1]) == 0
        因此该性质的必要性证明完毕
        充分性证明:
            假设字符串无此性质
            那么可以把字符串分成一下部分:
                [                 ]
                [             ]
                    [             ]
                                                           
            则n % (n - k) 一定不等于0
            否则上下两个窗口相互错位相等, 一定能推出字符串具有性质
        由此, 只需要判断n % (n - k) == 0即可等价判断是否具有此性质

*/
void solve(){
    string s;
    cin >> s;
    int n = s.size();
    vector<int> lps(n);
    int cur = 0;
    for(int i = 1; i < n; i++){
        while(cur > 0 && s[i] != s[cur]){
            cur = lps[cur - 1];
        }
        if(s[i] == s[cur]){
            lps[i] = ++cur;
        }
    }
    if(lps[n - 1] && n % (n - lps[n - 1]) == 0){
        cout << "YES\n";
    }
    else{
        cout << "NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
