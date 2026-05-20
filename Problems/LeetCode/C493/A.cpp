#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

class Solution {
public:
    int countCommas(int n) {
        i64 sum = 0;
        while(n >= 1000) {
            sum += n - 999;
            n /= 1000;
        }
        return sum;
    }
};