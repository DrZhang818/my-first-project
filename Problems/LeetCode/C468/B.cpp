#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll maxTotalValue(vector<int>& a, int k) {
        auto [mn, mx] = ranges::minmax(a);
        return 1LL * k * (mx - mn);
    }
};