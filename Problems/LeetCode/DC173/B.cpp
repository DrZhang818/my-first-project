#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
const int N = 100005;

int cnt[N];

class Solution {
public:
    int minLength(vector<int>& a, int k) {
        ll cur = 0;
        int n = a.size();
        int ans = inf;
        for(int l = 0, r = 0; r < n; r++) {
            if(++cnt[a[r]] == 1) {
                cur += a[r];
            }
            while(l < r) {
                if(cnt[a[l]] >= 2) {
                    cnt[a[l++]]--;
                } else if(cur - a[l] >= k) {
                    cur -= a[l];
                    cnt[a[l++]]--;
                } else {
                    break;
                }
            }
            if(cur >= k) {
                ans = min(ans, r - l + 1);
            }
        }
        for(int i = 0; i < n; i++) cnt[a[i]] = 0;
        return ans == inf ? -1 : ans;
    }
};