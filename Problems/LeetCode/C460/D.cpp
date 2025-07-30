#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef uint32_t u32;
typedef unsigned long long ull;
const int inf = 1000000000;

class XorBasis {
    vector<u32> b;
public:
    XorBasis(int n) : b(n) {}
    void insert(u32 x) {
        while(x) {
            int i = bit_width(x) - 1;
            if(b[i] == 0) {
                b[i] = x;
                return;
            }
            x ^= b[i];
        }
    }
    u32 max_xor() {
        u32 res = 0;
        for(int i = b.size() - 1; i >= 0; i--) {
            res = max(res, res ^ b[i]);
        }
        return res;
    }
};
class Solution {
public:
    ll maximizeXorAndXor(vector<int>& a) {
        int n = a.size();
        int sz = bit_width(u32(*max_element(a.begin(), a.end())));
        const int N = 1 << n;
        vector<int> sub_and(N), sub_xor(N), sub_or(N);
        sub_and[0] = -1;
        for(int i = 0; i < n; i++) {
            int x = a[i];
            int high_bit = 1 << i;
            for(int s = 0; s < high_bit; s++) {
                sub_and[high_bit | s] = sub_and[s] & x;
                sub_xor[high_bit | s] = sub_xor[s] ^ x;
                sub_or[high_bit | s] = sub_or[s] | x;
            }
        }
        sub_and[0] = 0;
        auto query = [&](int s) -> ll {
            XorBasis b(sz);
            int xor_ = sub_xor[s];
            for(int i = 0; i < n; i++) {
                if(s >> i & 1) {
                    b.insert(a[i] & ~xor_);
                }
            }
            return xor_ + 2LL * b.max_xor();
        };
        ll ans = 0;
        for(int i = 0; i < N; i++) {
            int j = (N - 1) ^ i;
            if(sub_and[i] + 2LL * sub_or[j] - sub_xor[j] > ans) {
                ans = max(ans, sub_and[i] + query(j));
            }
        }
        return ans;
    }
};