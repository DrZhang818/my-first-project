#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
template <int MOD> struct MInt {
    int x;
    constexpr MInt(i64 v = 0) : x(norm(v)) {
    }
    constexpr int val() const {
        return x;
    }
    constexpr static int getMod() {
        return MOD;
    }
    constexpr int norm(i64 v) const {
        v %= MOD;
        if(v < 0) {
            v += MOD;
        }
        return int(v);
    }
    constexpr MInt operator-() const {
        return MInt(x ? MOD - x : 0);
    }
    constexpr MInt& operator+=(MInt rhs) {
        i64 sum = i64(x) + rhs.x;
        x = int(sum >= MOD ? sum - MOD : sum);
        return *this;
    }
    constexpr MInt& operator-=(MInt rhs) {
        x -= rhs.x;
        if(x < 0) {
            x += MOD;
        }
        return *this;
    }
    constexpr MInt& operator*=(MInt rhs) {
        x = int(1LL * x * rhs.x % MOD);
        return *this;
    }
    constexpr MInt& operator/=(MInt rhs) {
        return *this *= rhs.inv();
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, MOD - 2);
    }
    friend constexpr MInt operator+(MInt a, MInt b) {
        return a += b;
    }
    friend constexpr MInt operator-(MInt a, MInt b) {
        return a -= b;
    }
    friend constexpr MInt operator*(MInt a, MInt b) {
        return a *= b;
    }
    friend constexpr MInt operator/(MInt a, MInt b) {
        return a /= b;
    }
    friend constexpr bool operator==(MInt a, MInt b) {
        return a.x == b.x;
    }
    friend constexpr bool operator!=(MInt a, MInt b) {
        return a.x != b.x;
    }
    friend constexpr bool operator<(MInt a, MInt b) {
        return a.x < b.x;
    }
};
template <int MOD> constexpr MInt<MOD> power(MInt<MOD> a, i64 b) {
    MInt<MOD> res = 1;
    while(b > 0) {
        if(b & 1) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }
    return res;
}
