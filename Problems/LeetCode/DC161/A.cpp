#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> minp, primes;
auto sieve = [] {
    minp.resize(100005);
    minp[0] = minp[1] = -1;
    for(int i = 2; i <= 100000; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(int p : primes) {
            if(i * p > 100000) {
                break;
            }
            minp[i * p] = p;
            if(minp[i] == p) {
                break;
            }
        }
    }
    return 0;
}();
class Solution {
public:
    ll splitArray(vector<int>& a) {
        ll ans = 0;
        for(int i = 0; i < a.size(); i++) {
            if(minp[i] == i) {
                ans += a[i];
            } else {
                ans -= a[i];
            }
        }
        return abs(ans);
    }
};