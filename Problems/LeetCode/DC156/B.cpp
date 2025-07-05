#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int minOperations(vector<int>& a) {
        int ans = 0, n = a.size();
        a.erase(unique(a.begin(), a.end()), a.end());
        n = a.size();
        int N = log2(n);
        a.insert(a.begin(), 0);
        vector<vector<int>> dp(n + 1, vector<int>(N + 1, inf));
        for(int i = 1; i <= n; i++) {
            dp[i][0] = a[i];
        }        
        for(int s = 1; s <= N; s++) {
            for(int i = 1; i + (1 << s - 1) <= n; i++) {
                dp[i][s] = min(dp[i][s - 1], dp[i + (1 << s - 1)][s - 1]);
            }
        }
        vector<int> idx(100005, 0);
        for(int i = 1; i <= n; i++) {
            if(a[i] == 0) continue;
            int pre = idx[a[i]];
            if(pre == 0) {
                ans++;
            }
            else {
                int mn = a[i];
                for(int s = N; s >= 0; s--) {
                    if(pre + (1 << s) < i) {
                        mn = min(mn, dp[pre][s]);
                        pre = pre + (1 << s);
                    }
                }
                mn = min(mn, dp[pre][0]);
                if(mn < a[i]) {
                    ans++;
                }
                cout << i << " " << a[i] << " " << mn << " \n";
            }

            idx[a[i]] = i;
        }
        return ans;
    }
};