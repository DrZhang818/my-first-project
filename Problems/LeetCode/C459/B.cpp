#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
const int inv2 = (MOD + 1) >> 1;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& a) {
        map<int,int> mp;
        for(int i = 0; i < a.size(); i++) {
            int y = a[i][1];
            mp[y]++;
        }
        int ans = 0, pre = 0;
        for(auto [_, c] : mp) {
            add(ans, 1LL * pre * c % MOD * (c - 1) % MOD * inv2 % MOD);
            add(pre, 1LL * c * (c - 1) % MOD * inv2 % MOD);
        }
        return ans;
    }
};