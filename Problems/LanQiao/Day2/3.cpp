#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

/*
    滑动窗口 || 频率统计
    题意:
        给定一个字符串s, 你需要删除一个子串, 并满足剩余字符串长度>=2且不能全是相同字符
        统计有多少种删除方式
    关键思考:
        观察后可以发现, 字符串具有以下单调性
        (1)字符串越长, 越可能不满足"全是相同字符"
        因此当我们发现删除[l,...,r]是合法的时候, [l+1,...,r]显然也满足
        因此遍历右端点r的时候维护左端点l即可
    代码实现:
        首先把字符串所有元素加入哈希表
        接着枚举右端点r, 使用滑动窗口经典方式
        1.入
            窗口内元素的为要删除的部分, 因此入窗即s[r]的次数减一
            如果s[r]次数变为0, 则从哈希表中移除
        2.出
            当窗口外元素种类小于2的时候(即所有元素相同)
            需要移除左端点, 即hash[s[l]]++, 并且左指针+1
        3.更新答案
            当窗口外元素种类大于等于2的时候即可更新答案, 方案数为r-l+1
            注意: 当种类大于等于2的时候, 长度一定不小于2, 因此长度要求自动满足
            否则需加入r - l + 1 <= n - len的判断(len为长度要求)
*/
void solve(){
    string s;
    cin >> s;
    ll cnt = 0;
    int n = s.length();
    unordered_map<char, int> hash;
    for(char c : s) hash[c]++;
    int l = 0;
    for(int r = 0; r < n; r++){
        hash[s[r]]--;
        if(hash[s[r]] == 0){
            hash.erase(s[r]);
        }
        while(l < r && hash.size() < 2){
            hash[s[l]]++;
            l++;
        }
        if(hash.size() >= 2){
            cnt += r - l + 1;
        }
    }
    cout << cnt << "\n";
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