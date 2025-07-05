#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    bool ck(char a, char b) {
        int d = abs(a - b);
        return d == 1 || d == 25;
    }
    string lexicographicallySmallestString(string s) {
        int n = s.size();
        s = "#" + s;
        vector dp1(n + 1, vector<bool>(n + 1));
        for(int len = 2; len <= n; len += 2) {
            for(int i = 1; i + len - 1 <= n; i++) {
                int j = i + len - 1;
                if(ck(s[i], s[j])) {
                    if(len == 2) {
                        dp1[i][j] = true;
                    } else {
                        dp1[i][j] = dp1[i + 1][j - 1];
                    }
                }
                for(int k = i + 1; !dp1[i][j] && k < j; k += 2) {
                    if(dp1[i][k] && dp1[k + 1][j]) {
                        dp1[i][j] = true;
                    }
                }
            }
        }
        vector<string> dp2(n + 2);
        for(int i = n; i >= 1; i--) {
            dp2[i] = s[i] + dp2[i + 1];
            for(int j = i + 1; j <= n; j += 2) {
                if(dp1[i][j]) {
                    dp2[i] = min(dp2[i], dp2[j + 1]);
                }
            }
        }
        return dp2[1];
    }
};