#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

class Solution {
public:
    int longestArithmetic(vector<int>& a) {
        int n = a.size();
        vector<int> pre(n + 1), suf(n + 1);
        pre[0] = suf[n - 1] = 1;
        int ans = 0;
        for(int i = 1; i < n; i++) {
            if(i == 1) {
                pre[i] = 2;
            } else {
                pre[i] = (a[i] - a[i - 1] == a[i - 1] - a[i - 2]) ? pre[i - 1] + 1 : 2;
            }
            ans = max(ans, pre[i]);
        }
        for(int i = n - 2; i >= 0; i--) {
            if(i == n - 2) {
                suf[i] = 2;
            } else {
                suf[i] = (a[i] - a[i + 1] == a[i + 1] - a[i + 2]) ? suf[i + 1] + 1 : 2;
            }
            ans = max(ans, suf[i]);
        }

        for(int i = 0; i < n; i++) {
            if(i == 0) {
                ans = max(ans, 1 + (i + 1 < n ? suf[i + 1] : 0));
            } else if(i == n - 1) {
                ans = max(ans, 1 + (i - 1 >= 0 ? pre[i - 1] : 0));
            } else {
                ans = max(ans, 1 + suf[i + 1]);
                ans = max(ans, 1 + pre[i - 1]);
                if((a[i + 1] - a[i - 1]) % 2 == 0) {
                    int d = (a[i + 1] - a[i - 1]) / 2;
                    ans = max(ans, 3);
                    if(i >= 2 && a[i - 1] - a[i - 2] == d) {
                        ans = max(ans, pre[i - 1] + 2);
                    }
                    if(i <= n - 3 && a[i + 2] - a[i + 1] == d) {
                        ans = max(ans, suf[i + 1] + 2);
                    }
                    if(i >= 2 && i <= n - 3 && a[i - 1] - a[i - 2] == d && a[i - 1] - a[i - 2] == a[i + 2] - a[i + 1]) {
                        ans = max(ans, pre[i - 1] + suf[i + 1] + 1);
                    }
                }
            }
        }
        return ans;
    }
};