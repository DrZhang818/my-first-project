#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;


class Solution {
public:
    bool completePrime(int num) {
        auto ck = [&](int x) {
            if(x == 1) {
                return false;
            }
            for(int i = 2; i * i <= x; i++) {
                if(x % i == 0) {
                    return false;
                }
            }
            return true;
        };

        string s = to_string(num);
        int x = 0;
        for(int i = 0; i < s.size(); i++) {
            int p = s[i] - '0';
            x = x * 10 + p;
            if(!ck(x)) {
                return false;
            }
        }
        x = 0;
        for(int i = s.size() - 1, j = 1; i >= 0; i--, j *= 10) {
            int p = s[i] - '0';
            x += p * j;
            if(!ck(x)) {
                return false;
            }
        }
        return true;
    }
};