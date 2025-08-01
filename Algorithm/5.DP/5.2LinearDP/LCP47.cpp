#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
class Solution {
public:
    int securityCheck(vector<int> &a, int k) {
        k++;
        int n = a.size();
        vector<int> dp(k + 1);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = k - a[i] + 1; j >= 0; j--) {
                add(dp[j + a[i] - 1], dp[j]);
            }
        }
        return dp[k - 1];
    }   
};