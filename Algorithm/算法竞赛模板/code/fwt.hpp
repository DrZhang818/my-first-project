#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int P = 998244353;
int powerMod(int a, i64 b) {
    int res = 1;
    while(b > 0) {
        if(b & 1) {
            res = int(1LL * res * a % P);
        }
        a = int(1LL * a * a % P);
        b >>= 1;
    }
    return res;
}
// OR 卷积变换：正变换 y += x，逆变换 y -= x
void fwtOr(vector<int>& a, bool inv) {
    int n = int(a.size());
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += len << 1) {
            for(int j = 0; j < len; j++) {
                int& x = a[i + j];
                int& y = a[i + j + len];
                if(!inv) {
                    y += x;
                    if(y >= P) {
                        y -= P;
                    }
                } else {
                    y -= x;
                    if(y < 0) {
                        y += P;
                    }
                }
            }
        }
    }
}
// AND 卷积变换：正变换 x += y，逆变换 x -= y
void fwtAnd(vector<int>& a, bool inv) {
    int n = int(a.size());
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += len << 1) {
            for(int j = 0; j < len; j++) {
                int& x = a[i + j];
                int& y = a[i + j + len];
                if(!inv) {
                    x += y;
                    if(x >= P) {
                        x -= P;
                    }
                } else {
                    x -= y;
                    if(x < 0) {
                        x += P;
                    }
                }
            }
        }
    }
}
// XOR 卷积变换：(x, y) -> (x + y, x - y)，逆变换同蝴蝶再乘 n^{-1}
void fwtXor(vector<int>& a, bool inv) {
    int n = int(a.size());
    for(int len = 1; len < n; len <<= 1) {
        for(int i = 0; i < n; i += len << 1) {
            for(int j = 0; j < len; j++) {
                int x = a[i + j];
                int y = a[i + j + len];
                a[i + j] = x + y >= P ? x + y - P : x + y;
                a[i + j + len] = x - y < 0 ? x - y + P : x - y;
            }
        }
    }
    if(inv) {
        int invN = powerMod(n, P - 2);
        for(int& v : a) {
            v = int(1LL * v * invN % P);
        }
    }
}
vector<int> convOr(vector<int> a, vector<int> b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    for(int& x : a) {
        x = (x % P + P) % P;
    }
    for(int& x : b) {
        x = (x % P + P) % P;
    }
    int n = 1;
    while(n < int(max(a.size(), b.size()))) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    fwtOr(a, false);
    fwtOr(b, false);
    for(int i = 0; i < n; i++) {
        a[i] = int(1LL * a[i] * b[i] % P);
    }
    fwtOr(a, true);
    return a;
}
vector<int> convAnd(vector<int> a, vector<int> b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    for(int& x : a) {
        x = (x % P + P) % P;
    }
    for(int& x : b) {
        x = (x % P + P) % P;
    }
    int n = 1;
    while(n < int(max(a.size(), b.size()))) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    fwtAnd(a, false);
    fwtAnd(b, false);
    for(int i = 0; i < n; i++) {
        a[i] = int(1LL * a[i] * b[i] % P);
    }
    fwtAnd(a, true);
    return a;
}
vector<int> convXor(vector<int> a, vector<int> b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    for(int& x : a) {
        x = (x % P + P) % P;
    }
    for(int& x : b) {
        x = (x % P + P) % P;
    }
    int n = 1;
    while(n < int(max(a.size(), b.size()))) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    fwtXor(a, false);
    fwtXor(b, false);
    for(int i = 0; i < n; i++) {
        a[i] = int(1LL * a[i] * b[i] % P);
    }
    fwtXor(a, true);
    return a;
}
