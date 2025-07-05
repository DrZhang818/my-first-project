#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int minOperations(string s, string t) {
        int n = s.size();
        s = "#" + s, t = "#" + t;
        vector f(n + 1, vector<int>(n + 1));
        for(int i = 1; i <= n; i++) {
            int cnt[26][26]{}, c1 = 0;
            for(int j = i; j <= n; j++) {
                int u = s[j] - 'a', v = t[j] - 'a';
                if(u != v) {
                    if(cnt[v][u]) {
                        cnt[v][u]--;
                    } else {
                        cnt[u][v]++;
                        c1++;
                    }
                }
                int rev_cnt[26][26]{}, c2 = 1;
                for(int k = i; k <= j; k++) {
                    u = s[k] - 'a', v = t[i + j - k] - 'a';
                    if(u == v) continue;
                    if(rev_cnt[v][u]) {
                        rev_cnt[v][u]--;
                    } else {
                        rev_cnt[u][v]++;
                        c2++;
                    }
                }
                f[i][j] = min(c1, c2);
            }
        }
        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= i; j++) {
                dp[i] = min(dp[i], dp[j - 1] + f[j][i]);
            }
        }
        return dp[n];
    }
};