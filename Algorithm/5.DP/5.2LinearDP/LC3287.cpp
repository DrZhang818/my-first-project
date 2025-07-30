#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int maxValue(vector<int>& a, int k) {
        int n = a.size();
        int suf[n + 1][k + 1][1 << 7];
        memset(suf, 0, sizeof(suf));
        suf[n][0][0] = 1;
        suf[n][0][0] = 1;
        for(int i = n - 1; i >= k; i--) {
            int x = a[i];
            for(int j = 0; j <= k; j++) {
                for(int s = 0; s < 1 << 7; s++) {
                    suf[i][j][s] |= suf[i + 1][j][s];
                    if(j) suf[i][j][s | x] |= suf[i + 1][j - 1][s];
                }
            }
        }
        int pre[k + 1][1 << 7];
        memset(pre, 0, sizeof(pre));
        pre[0][0] = 1;
        int ans = 0;
        for(int i = 0; i < n - k; i++) {
            int x = a[i];
            for(int j = k; j >= 1; j--) {
                for(int s = 0; s < 1 << 7; s++) {
                    pre[j][s | x] |= pre[j - 1][s];
                }
            }
            if(i >= k - 1) {
                for(int s = 0; s < 1 << 7; s++) {
                    if(pre[k][s]) {
                        for(int t = 0; t < 1 << 7; t++) {
                            if(suf[i + 1][k][t]) {
                                ans = max(ans, s ^ t);
                            }
                        }
                    }
                }
            }
            if(ans == (1 << 7) - 1) {
                return ans;
            }
        }   
        return ans;
    }
};