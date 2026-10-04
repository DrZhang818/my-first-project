#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int FPS_MOD = 998244353;
constexpr int FPS_G = 3;
int fpsPower(int a, int b) {
    a %= FPS_MOD;
    if(a < 0) {
        a += FPS_MOD;
    }
    int res = 1;
    while(b > 0) {
        if(b & 1) {
            res = int(1LL * res * a % FPS_MOD);
        }
        a = int(1LL * a * a % FPS_MOD);
        b >>= 1;
    }
    return res;
}
void fpsNtt(vector<int>& a, bool invert) {
    int n = int(a.size());
    if(n <= 1) {
        return;
    }
    assert((n & (n - 1)) == 0);
    assert((FPS_MOD - 1) % n == 0);
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while(j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 2; len <= n; len <<= 1) {
        int wlen = fpsPower(FPS_G, (FPS_MOD - 1) / len);
        if(invert) {
            wlen = fpsPower(wlen, FPS_MOD - 2);
        }
        int half = len >> 1;
        for(int left = 0; left < n; left += len) {
            i64 w = 1;
            for(int j = 0; j < half; j++) {
                int u = a[left + j];
                int v = int(w * a[left + j + half] % FPS_MOD);
                int sum = u + v;
                if(sum >= FPS_MOD) {
                    sum -= FPS_MOD;
                }
                int diff = u - v;
                if(diff < 0) {
                    diff += FPS_MOD;
                }
                a[left + j] = sum;
                a[left + j + half] = diff;
                w = w * wlen % FPS_MOD;
            }
        }
    }
    if(invert) {
        int invN = fpsPower(n, FPS_MOD - 2);
        for(int& x : a) {
            x = int(1LL * x * invN % FPS_MOD);
        }
    }
}
vector<int> fpsConvTrunc(vector<int> a, vector<int> b, int limit) {
    if(limit <= 0) {
        return {};
    }
    if(int(a.size()) > limit) {
        a.resize(limit);
    }
    if(int(b.size()) > limit) {
        b.resize(limit);
    }
    if(a.empty() || b.empty()) {
        return vector<int>(limit, 0);
    }
    int resSize = int(a.size() + b.size() - 1);
    if(1LL * a.size() * b.size() <= 4096) {
        vector<int> c(min(resSize, limit), 0);
        for(int i = 0; i < int(a.size()); i++) {
            for(int j = 0; j < int(b.size()) && i + j < limit; j++) {
                c[i + j] = int((c[i + j] + 1LL * a[i] * b[j]) % FPS_MOD);
            }
        }
        return c;
    }
    int n = 1;
    while(n < resSize) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    fpsNtt(a, false);
    fpsNtt(b, false);
    for(int i = 0; i < n; i++) {
        a[i] = int(1LL * a[i] * b[i] % FPS_MOD);
    }
    fpsNtt(a, true);
    a.resize(min(resSize, limit));
    return a;
}
// a(x)^(-1) mod x^limit，要求 a[0] != 0
vector<int> polyInv(const vector<int>& a, int limit) {
    if(limit <= 0) {
        return {};
    }
    assert(!a.empty() && a[0] != 0);
    vector<int> b{fpsPower(a[0], FPS_MOD - 2)};
    while(int(b.size()) < limit) {
        int len = min(2 * int(b.size()), limit);
        vector<int> f(min(int(a.size()), len));
        copy(a.begin(), a.begin() + int(f.size()), f.begin());
        vector<int> t = fpsConvTrunc(f, b, len);
        t.resize(len);
        for(int& x : t) {
            if(x != 0) {
                x = FPS_MOD - x;
            }
        }
        t[0] += 2;
        if(t[0] >= FPS_MOD) {
            t[0] -= FPS_MOD;
        }
        b = fpsConvTrunc(b, t, len);
        b.resize(len);
    }
    return b;
}
// ln(a(x)) mod x^limit，要求 a[0] != 0（通常为 1）
vector<int> polyLog(const vector<int>& a, int limit) {
    if(limit <= 0) {
        return {};
    }
    assert(!a.empty() && a[0] != 0);
    vector<int> inv = polyInv(a, limit);
    vector<int> der(min(int(a.size()) - 1, limit));
    for(int i = 0; i < int(der.size()); i++) {
        der[i] = int(1LL * a[i + 1] * (i + 1) % FPS_MOD);
    }
    vector<int> prod = fpsConvTrunc(der, inv, limit);
    prod.resize(limit, 0);
    vector<int> invInt(limit + 1, 1);
    for(int i = 2; i <= limit; i++) {
        invInt[i] = int(1LL * (FPS_MOD - FPS_MOD / i) * invInt[FPS_MOD % i] % FPS_MOD);
    }
    vector<int> res(limit, 0);
    for(int i = 1; i < limit; i++) {
        res[i] = int(1LL * prod[i - 1] * invInt[i] % FPS_MOD);
    }
    return res;
}
// exp(a(x)) mod x^limit，要求 a[0] == 0
vector<int> polyExp(const vector<int>& a, int limit) {
    if(limit <= 0) {
        return {};
    }
    assert(a.empty() || a[0] == 0);
    vector<int> b{1};
    while(int(b.size()) < limit) {
        int len = min(2 * int(b.size()), limit);
        vector<int> lb = polyLog(b, len);
        vector<int> f(len, 0);
        for(int i = 0; i < len && i < int(a.size()); i++) {
            f[i] = a[i];
        }
        for(int i = 0; i < len; i++) {
            f[i] = (f[i] - lb[i] + FPS_MOD) % FPS_MOD;
        }
        f[0] = (f[0] + 1) % FPS_MOD; // 1 + a - ln(b)
        b = fpsConvTrunc(b, f, len);
        b.resize(len);
    }
    return b;
}
