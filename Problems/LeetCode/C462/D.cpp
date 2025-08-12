#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E18;
const int ODD_MASK = 0x155;
const int D = 9;
int sz[1 << D];
int init = []() {
    for(int s = 1; s < 1 << D; s++) {
        int t = s & ODD_MASK;
        if(t & (t - 1)) continue;
        for(int i = 0; i < D; i++) {
            if(s >> i & 1) {
                sz[s] += i + 1;
            }
        }
    }
    return 0;
}();
ll get(vector<int> &a, int odd) {
    ll res = 0;
    for(int i = 0; i < a.size(); i++) {
        res = res * 10 + a[i];
    }
    if(odd) res = res * 10 + odd;
    for(int i = a.size() - 1; i >= 0; i--) {
        res = res * 10 + a[i];
    }
    return res;
}
class Solution {
public:
    ll specialPalindrome(ll n) {
        int len = to_string(n).size();
        ll ans = LLONG_MAX;
        for(int s = 1; s < 1 << D; s++) {
            int cnt = sz[s];
            if(cnt != len && cnt != len + 1) {
                continue;
            }
            vector<int> p;
            int odd = 0;
            for(int x = 1; x <= D; x++) {
                if(s >> (x - 1) & 1) {
                    p.insert(p.end(), x >> 1, x);
                    if(x & 1) {
                        odd = x;
                    }
                }
            }
            do {
                ll cur = get(p, odd);
                if(cur >= ans) break;
                if(cur > n) {
                    ans = cur;
                    break;
                }
            } while(next_permutation(p.begin(), p.end()));
        }
        return ans;
    }
};
