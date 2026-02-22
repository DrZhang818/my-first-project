#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

int fac[10];
auto init = []() -> int {
    fac[0] = 1;
    for(int i = 1; i < 10; i++) {
        fac[i] = fac[i - 1] * i;
    }
    return 1;
}();

class Solution {
public:
    bool isDigitorialPermutation(int n) {
        int cnt[10];
        int cur = 0;
        i64 sum = 0;
        while(n) {
            sum += fac[n % 10];
            cnt[n % 10]++;            
            n /= 10;
        }        
        while(sum) {
            cnt[sum % 10]--;
            sum /= 10;
        }
        for(int i = 0; i < 10; i++) {
            if(cnt[i] != 0) {
                return false;
            }
        }
        return true;
    }
};