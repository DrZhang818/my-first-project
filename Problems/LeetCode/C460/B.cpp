#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll numOfSubsequences(string s) {
        int n = s.size();
        s = "#" + s;
        vector<array<ll,3>> pre(n + 2), suf(n + 2); 
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1];
            if(s[i] == 'L') {
                pre[i][0]++;
            } else if(s[i] == 'C') {
                pre[i][1] += pre[i][0];
            } else if(s[i] == 'T') {
                pre[i][2] += pre[i][1];
            }
        }
        for(int i = n; i >= 1; i--) {
            suf[i] = suf[i + 1];
            if(s[i] == 'T') {
                suf[i][0]++;
            } else if(s[i] == 'C') {
                suf[i][1] += suf[i][0];
            } else if(s[i] == 'L') {
                suf[i][2] += suf[i][1];
            }
        }
        ll ans = 0;
        for(int i = 0; i <= n; i++) {
            ans = max(ans, pre[i][2] + suf[i + 1][2] + (pre[i][0] + 1) * suf[i + 1][1] + pre[i][1] * suf[i + 1][0]);
            ans = max(ans, pre[i][2] + suf[i + 1][2] + pre[i][0] * suf[i + 1][1] + pre[i][1] * suf[i + 1][0] + pre[i][0] * suf[i + 1][0]);
            ans = max(ans, pre[i][2] + suf[i + 1][2] + pre[i][1] * (suf[i + 1][0] + 1) + pre[i][0] * suf[i + 1][1]);
        }
        return ans;
    }
};