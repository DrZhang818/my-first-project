#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

class Solution {
public:
    i64 countCommas(i64 n) {
        i64 sum = 0;
        for(i64 p = 1000; p <= n; p *= 1000) {
            sum += max(0LL, n - p + 1);
        }
        return sum;
    }
};