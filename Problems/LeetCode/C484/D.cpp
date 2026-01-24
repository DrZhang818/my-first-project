#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int maximumAND(vector<int>& a, int k, int m) {
        int ans = 0;
        for(int i = 30; i >= 0; i--) {
            sort(a.begin(), a.end(), greater<int>());
            ll need = 0;
            for(int j = 0; j < m; j++) {
                if(~a[j] >> i & 1) {
                    need += (1 << i) - a[j];
                } 
            }
            if(need <= k) {
                k -= need;
                ans += 1 << i;
                for(int j = a.size() - 1; j >= 0; j--) {
                    if(a[j] >> i & 1) {
                        a[j] ^= 1 << i;
                    } else if(j >= m) {
                        a.pop_back();
                    } else {
                        a[j] = 0;
                    }
                }
            } else {
                for(int j = 0; j < a.size(); j++) {
                    a[j] &= ~(1 << i);
                }
            }
        }
        return ans;
    }
};