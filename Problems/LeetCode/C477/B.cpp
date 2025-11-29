#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int maxBalancedSubarray(vector<int>& a) {
        int n = a.size();
        a.insert(a.begin(), 0);
        vector<int> _xor(n + 1), w(n + 1);
        for(int i = 1; i <= n; i++) {
            _xor[i] = _xor[i - 1] ^ a[i];
            w[i] = w[i - 1] + (a[i] % 2 == 0 ? 1 : -1);
        }
        int ans = 0;
        map<PII,int> mp;
        mp[{0, 0}] = 0;
        for(int i = 1; i <= n; i++) {
            PII cur = {_xor[i], w[i]};
            if(mp.contains(cur)) {
                ans = max(ans, i - mp[cur]);
            } else {
                mp[cur] = i;
            }
        }
        return ans;
    }
};