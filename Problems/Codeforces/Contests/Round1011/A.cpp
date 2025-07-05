#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://codeforces.com/contest/2085/problem/A
/*
    构造 || 贪心
    题意:
        给定一个长度为n的字符串S, 定义一个字符串是合法的, 当且仅当字符串小于它的逆序
        现有k次操作, 每次操作为:
        op: 选择两个索引i,j, 交换s[i]与s[j]
        判断能否在至多操作k次的情况下使得字符串成为合法字符串
        范围: n∈[1,100], k∈[0,1e4]
    关键思考:
        本题为构造类题目, 常用思考方式为: 从小规模数据中探寻规律, 从特殊到一般
        很容易发现, 本题的k属于越大越合法的类型, 具有单调性
        这时我们就可以尝试从小到大思考k的取值, 看看能否找到不合法->合法的分界点
        首先考虑k = 0的情况, 这种属于0自由度(静止)状态
        则只需判断S是否小于S'即可
        当k >= 1时, 我们很自然的有个贪心想法: 从左到右放置字典序最小的字符
        进一步地, 我们只需让s[1] < s[n]即可
        考虑以下三种情况:
            (1)s[1] < s[n], 此时已经符合
            (2)s[1] > s[n], 交换s[1]和s[n]
            (3)s[1] = s[n], 此时可以把最大的字符给s[n], 如果s[n]已经最大, 则把最小的给s[1]
        我们发现, 情况(3)有一种特例为: 整个字符串最大字符 = 最小字符
        这种情况等价于字符串只有一种字符, 则此时无法构造
        因此, 只要字符串字符种类大于1, 就可以通过一次操作得到合法字符串 
*/
void solve() { 
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;
    map<char, int> mp;
    int cnt = 0;
    for(auto c : s) {
        if(!mp[c]) cnt++;
        mp[c]++;
    }
    string t = s;
    reverse(t.begin(), t.end());
    if(k == 0) {
        if(s < t) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
        return;
    }
    if(cnt <= 1) {
        cout << "NO\n";
    }  else {
        cout << "YES\n";
    }
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
