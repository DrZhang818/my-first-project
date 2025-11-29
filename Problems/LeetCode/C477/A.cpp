#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    ll sumAndMultiply(int n) {
        ll x = 0, y = 0;
        int m = 1000000000;
        for(int i = 9; i >= 0; i--) {
            int p = n / m % 10;
            if(p) {
                x = x * 10 + p;
                y += p;
            }
            m /= 10;
        }
        return x * y;
    }
};
