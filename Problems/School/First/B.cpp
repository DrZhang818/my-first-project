#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


//https://vjudge.net/contest/700331#problem/B
/*
    模拟
    题意:
        给定一个字符串, 定义元音字母包括"aeiouy" 
        要求按照下述规则转化字符串:
        (1)删除所有元音字母(不区分大小写)
        (2)在每个辅音字母前插入字符'.'(不区分大小写)
        (3)将所有大写辅音字母转化成对应的小写字母
    关键思考:
        本题为模拟类题目, 需要读请题意, 采用合适的算法和数据结构维护题目信息
        注意元音字母包含y
*/
const string ch = "aeiouy";
bool is_vowel(char c) {
    return ch.find(tolower(c)) != -1;
}
void solve() { 
    string s;
    cin >> s;
    for(auto c : s) {
        if(is_vowel(c)) continue;
        cout << "." << (char)tolower(c);
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
