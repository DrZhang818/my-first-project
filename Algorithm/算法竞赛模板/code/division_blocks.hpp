#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128_t;
i64 sumFloorDiv(i64 n, i64 k) {
    i128 ans = 0;
    for(i64 l = 1, r; l <= n; l = r + 1) {
        i64 v = k / l;
        if(v == 0) {
            r = n;
        } else {
            r = min(n, k / v);
        }
        ans += i128(r - l + 1) * v;
    }
    return i64(ans);
}
