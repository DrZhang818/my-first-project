#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using cdb = complex<db>;
void fft(vector<cdb>& a, bool invert) {
    int n = int(a.size());
    for(int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for(; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;
        if(i < j) {
            swap(a[i], a[j]);
        }
    }
    for(int len = 2; len <= n; len <<= 1) {
        db ang = 2 * acos(-1.0) / len * (invert ? -1 : 1);
        cdb wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len) {
            cdb w(1);
            for(int j = 0; j < len / 2; j++) {
                cdb u = a[i + j];
                cdb v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if(invert) {
        for(cdb& x : a) {
            x /= n;
        }
    }
}
vector<i64> convolutionFft(const vector<int>& a, const vector<int>& b) {
    if(a.empty() || b.empty()) {
        return {};
    }
    int need = int(a.size() + b.size() - 1);
    int n = 1;
    while(n < need) {
        n <<= 1;
    }
    vector<cdb> A(n), B(n);
    for(int i = 0; i < int(a.size()); i++) {
        A[i] = a[i];
    }
    for(int i = 0; i < int(b.size()); i++) {
        B[i] = b[i];
    }
    fft(A, false);
    fft(B, false);
    for(int i = 0; i < n; i++) {
        A[i] *= B[i];
    }
    fft(A, true);
    vector<i64> res(need);
    for(int i = 0; i < need; i++) {
        res[i] = llround(A[i].real());
    }
    return res;
}
