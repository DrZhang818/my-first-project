#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int longestSubarray(vector<int>& a) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<int> pre(n + 1), suf(n + 2);
        pre[1] = suf[n] = 1;
        for(int i = 2; i <= n; i++) {
            pre[i] = a[i] >= a[i - 1] ? pre[i - 1] + 1 : 1;
        }    
        for(int i = n - 1; i >= 1; i--) {
            suf[i] = a[i] <= a[i + 1] ? suf[i + 1] + 1 : 1;
        }
        int ans = 1;
        for(int i = 1; i <= n; i++) {
            if(i != 1 && i != n && a[i - 1] <= a[i + 1]) {
                ans = max(ans, pre[i - 1] + suf[i + 1] + 1);
            } else {
                ans = max({ans, pre[i - 1] + 1, suf[i + 1] + 1});
            }
        }
        return ans;
    }   
};