#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;

//https://leetcode.cn/problems/rearrange-k-substrings-to-form-target-string/
/*
    哈希表 || 排序
    判断 s 子串和 t 子串排序后的结果是否一样。也可以用哈希表统计每个子串的出现次数。
*/

//哈希表做法 O(n)
class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k) {
        int n = s.length();
        k = n / k;
        unordered_map<string, int> cnt_s;
        unordered_map<string, int> cnt_t;
        for(int i = 0; i < n; i += k){
            string chunk_s = s.substr(i, k);
            cnt_s[chunk_s]++;

            string chunk_t = t.substr(i, k);
            cnt_t[chunk_t]++;
        }
        return cnt_s == cnt_t;
    }
};
//排序做法 O(nlogn)
class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k) {
        int n = s.length();
        vector<string> a, b;
        k = n / k;
        for(int i = 0; i < n; i += k){
            a.push_back(s.substr(i, k));
            b.push_back(t.substr(i, k));
        }   
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        return a == b;
    }
};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    solve();
    return 0;
}
