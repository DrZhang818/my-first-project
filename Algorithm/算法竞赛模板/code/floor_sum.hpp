#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;
struct FSResult {
    i64 f, g, h;
};
FSResult floorSumCalc(i128 n, i128 a, i128 b, i128 c) {
    if(n < 0) {
        return {0, 0, 0};
    }
    i128 A = a / c;
    if(a % c != 0 && a < 0) {
        A--;
    }
    i128 B = b / c;
    if(b % c != 0 && b < 0) {
        B--;
    }
    i128 ra = a - A * c;
    i128 rb = b - B * c;
    if(A != 0 || B != 0) {
        FSResult t = floorSumCalc(n, ra, rb, c);
        i128 s0 = n + 1;
        i128 s1 = n * (n + 1) / 2;
        i128 s2 = n * (n + 1) * (2 * n + 1) / 6;
        return {i64(A * s1 + B * s0 + t.f), i64(A * s2 + B * s1 + t.g),
                i64(A * A * s2 + 2 * A * B * s1 + B * B * s0 + 2 * A * t.g + 2 * B * t.f +
                    t.h)};
    }
    if(a == 0) {
        return {0, 0, 0};
    }
    i128 m = (a * n + b) / c;
    if(m == 0) {
        return {0, 0, 0};
    }
    FSResult t = floorSumCalc(m - 1, c, c - b - 1, a);
    return {i64(n * m - t.f), i64(m * n * (n + 1) / 2 - (t.f + t.h) / 2),
            i64(n * m * m - t.f - 2 * t.g)};
}
FSResult floorSum(i64 n, i64 a, i64 b, i64 c) {
    if(c <= 0) {
        return {0, 0, 0};
    }
    return floorSumCalc(n, a, b, c);
}
