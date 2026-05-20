#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 1E5;

vector<int> divs[N + 1];
auto init = []() {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            divs[j].push_back(i);
        }
    }
    return 1;
}();


class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();      
        int ans = 0;

        vector<int> suf(n, n);
        for(int i = n - 2; i >= 0; i--) {
            if(nums[i] > nums[i + 1]) {
                suf[i] = i + 1;
            } else {
                suf[i] = suf[i + 1];
            }
        }

        for(int k : divs[n]) {
            int las = -inf;
            bool ok = true;

            for(int i = 0; i < n; i += k) {
                int j = suf[i];
                if(j >= i + k) {
                    if(nums[i] < las) {
                        ok = false;
                        break;
                    }
                    las = nums[i + k - 1];
                } else {
                    int r = suf[j];
                    if(r < i + k || nums[i] < nums[i + k - 1] || nums[j] < las) {
                        ok = false;
                        break;
                    }
                    las = nums[j - 1];
                }
            }

            if(ok) {
                ans += k;
            }
        }
        return ans;
    }
};