#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/shift-distance-between-two-strings/
/*
    模拟/前缀和优化
    目标: 从s到t的最小路径和，由于路径连续，可以用前缀和优化
          当然本题也可直接模拟(由于字母表共26个字母，可作为常数忽略)
    关键: 处理环形数组的问题————断环成链 or 正难则反
*/

//前缀和 ———— 断环成链
class Solution {
public:
    ll shiftDistance(string s, string t, vector<int>& nxtC, vector<int>& preC) {
        const int SIGMA = 26;
        ll suffix[SIGMA * 2 + 1]{}, prefix[SIGMA * 2 + 1]{};
        for(int i = 0; i < SIGMA * 2; i++){
            suffix[i + 1] = suffix[i] + nxtC[i % SIGMA];
            prefix[i + 1] = prefix[i] + preC[i % SIGMA];
        }
        ll ans = 0;
        for(int i = 0; i < s.length(); i++){
            int x = s[i] - 'a', y = t[i] - 'a';
            ans += min(suffix[x <= y ? y : y + SIGMA] - suffix[x],
                       prefix[(x >= y ? x : x + SIGMA) + 1] - prefix[y + 1]);
        }
        return ans;
    }
};
//前缀和 ———— 正难则反
class Solution {
public:
typedef long long ll;
    ll shiftDistance(string s, string t, vector<int>& nxtC, vector<int>& preC) {
        ll ans = 0;
        vector<ll> prefix(27), suffix(27);
        for(int i = 0; i < 26; i++){
            prefix[i + 1] = prefix[i] + preC[i];
            suffix[i + 1] = suffix[i] + nxtC[i];
        }
        ll preSum = prefix[26], sufSum = suffix[26];
        for(int i = 0; i < s.length(); i++){
            int c = s[i] - 'a';
            int tar = t[i] - 'a';
            ll pre = 0, suf = 0;
            if(c == tar) continue;
            if(c < tar){
                suf = suffix[tar] - suffix[c];
                pre = preSum - (prefix[tar + 1] - prefix[c + 1]);
            }
            else{
                suf = sufSum - (suffix[c] - suffix[tar]);
                pre = prefix[c + 1] - prefix[tar + 1];
            }
            ans += min(pre, suf);
        }
        return ans;
    }
};
//模拟
class Solution {
public:
typedef long long ll;
    ll shiftDistance(string s, string t, vector<int>& nxtC, vector<int>& preC) {
        ll ans = 0;
        for(int i = 0; i < s.length(); i++){
            char c = s[i], tar = t[i];
            ll pre = 0, suf = 0;
            while(c != tar){
                suf += nxtC[c - 'a'];
                c = (c == 'z') ? 'a' : c + 1;
            }
            c = s[i], tar = t[i];
            while(c != tar){
                pre += preC[c - 'a'];
                c = (c == 'a') ? 'z' : c - 1;
            }
            ans += min(pre, suf);
        }
        return ans;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    
    return 0;
}





