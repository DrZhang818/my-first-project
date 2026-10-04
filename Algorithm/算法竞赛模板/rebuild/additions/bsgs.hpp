#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;
struct BSGS {
    static i64 mul(i64 a, i64 b, i64 m) {
        return i128(a) * b % m;
    }
    static i64 power(i64 a, i64 b, i64 m) {
        i64 r = 1 % m;
        for(; b; b >>= 1, a = mul(a, a, m)) {
            if(b & 1) {
                r = mul(r, a, m);
            }
        }
        return r;
    }
    static i64 inv(i64 a, i64 m) {
        i128 x = 1, y = 0, u = 0, v = 1;
        i64 b = m;
        while(b) {
            i64 q = a / b, r = a % b;
            a = b;
            b = r;
            i128 z = x - q * u;
            x = u;
            u = z;
            z = y - q * v;
            y = v;
            v = z;
        }
        return (x % m + m) % m;
    }
    // Smallest x >= 0 with a^x = b (mod m); -1 if impossible.
    static i64 solve(i64 a, i64 b, i64 m) {
        assert(m > 0);
        if(m == 1) {
            return 0;
        }
        a = (i128(a) % m + m) % m;
        b = (i128(b) % m + m) % m;
        if(b == 1) {
            return 0;
        }
        i64 k = 1, cnt = 0, g;
        while((g = gcd(a, m)) > 1) {
            if(b % g) {
                return -1;
            }
            b /= g;
            m /= g;
            k = mul(k, a / g, m);
            ++cnt;
            if(k == b) {
                return cnt;
            }
        }
        b = mul(b, inv(k, m), m);
        i64 n = sqrtl(m) + 1, cur = 1 % m;
        unordered_map<i64, i64> mp;
        mp.reserve(n * 2);
        for(i64 j = 0; j < n; j++) {
            if(!mp.count(cur)) {
                mp[cur] = j;
            }
            cur = mul(cur, a, m);
        }
        i64 step = inv(power(a, n, m), m);
        cur = b;
        for(i64 i = 0; i <= n; i++) {
            auto it = mp.find(cur);
            if(it != mp.end()) {
                return cnt + i * n + it->second;
            }
            cur = mul(cur, step, m);
        }
        return -1;
    }
};
