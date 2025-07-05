#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


//https://codeforces.com/contest/2048/problem/C
/*
    字符串 || 位运算 || 贪心思维 || 本题也有Z函数写法
    从二进制字符串中选取两个子串以最大化其异或值
    题意: 
        给定一个二进制字符串s, 你的任务是从中选出两个子串, 使得两个子串的异或值最大
    关键思考:
        首先, 字符串的首位保证是1, 那么一定有一个字串就是字符串本身, 否则得到的结果
        位数一定更小, 这样答案总是劣的
        对于另一个字符串, 考虑异或的性质, 尽量让字符串对齐的位置不相同
        而为了最大化结果, 考虑如下贪心：
            1.对于原串中最高位的0, 希望找到1与之对齐
            2.对于原串中为1的位置, 希望找到0与之对齐
        那么第二个串的长度实际上就由最高位的0来决定, 并且可以得到一个长度为k的期望子串
        接着枚举所有长度为k的子串, 按照它与期望子串的对应程度来排序, 程度最高的就是答案
        对应程度可以由以下方法衡量:
            把匹配的位置设为1, 最后的字典序大小就可以等价表示对应程度的大小
*/
void solve(){
    string s;
    cin >> s;
    int n = s.size();
    int l1 = 1, r1 = s.size();
    int len = 0;
    string temp;
    int ok = 0;
    for(int i = 0; i < n; i++){
        if(!ok && s[i] == '0'){
            len = s.size() - i;
            ok = 1;
        }
        if(ok){
            temp += (s[i] == '0' ? '1' : '0');
        }
    }
    if(temp.empty()){
        cout << l1 << " " << r1 << " " << 1 << " " << 1 << "\n";
        return;
    }
    int l2 = 1, r2 = 1;
    string maxmatch(len, '0');
    for(int i = 0; i < s.size() - len; i++){
        string curmatch(len, '0');
        string cur = s.substr(i, len);
        for(int j = 0; j < len; j++){
            if(cur[j] == temp[j]){
                curmatch[j] = '1';
            }
        }
        if(curmatch > maxmatch){
            l2 = i + 1;
            r2 = l2 + len - 1;
            maxmatch = curmatch;
        }
    }
    cout << l1 << " " << r1 << " " << l2 << " " << r2 << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
