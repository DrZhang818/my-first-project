#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();

        int c0 = 0, c1 = 0;
        vector<int> pre(n + 1);
        for(int i = 1; i <= n; i++) {
            pre[i] = pre[i - 1] + ((s[i - 1] == '1') ? 1 : -1);
            c0 += (s[i - 1] == '0');
            c1 += (s[i - 1] == '1');
        }

        int ans = 0;
        vector<array<int, 2>> las(2 * n + 1, {-1, -1});
        las[n][0] = 0;

        for(int i = 1; i <= n; i++) {
            int x = pre[i] + n;
            for(int d : {-2, 0, 2}) {
                int val = x + d;
                if(val < 0 || val > 2 * n) continue;
                for(int j : las[val]) {
                    if(j == -1) break;
                    int len = i - j;
                    if(d == -2 && (len - 2) / 2 == c0) continue;
                    if(d == 2  && (len - 2) / 2 == c1) continue;
                    ans = max(ans, len);
                }
            }
            for(int& j : las[x]) {
                if(j == -1) {
                    j = i;
                    break;
                }
            }
        }

        return ans;
    }
};