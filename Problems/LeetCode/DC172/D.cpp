#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    ll lastInteger(ll n) {
        auto dfs = [&](this auto &&self, ll x, int tag) -> ll {
            if(x == 1) {
                return 1;
            }
            return self(x + 1 >> 1, tag ^ 1) * 2 - (x & 1 | tag & 1);
        };
        return dfs(n, 1);
    }
};