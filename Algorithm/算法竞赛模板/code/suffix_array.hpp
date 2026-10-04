#pragma once
#include <bits/stdc++.h>
using namespace std;
struct SA {
    int n;
    vector<int> sa, rk, height;
    SA(const string& str) {
        n = int(str.size());
        sa.assign(n + 1, 0);
        rk.assign(n + 1, 0);
        height.assign(n + 1, 0);
        if(n == 0) {
            return;
        }
        // 追加最小哨兵，使循环移位排序等价于后缀排序
        string t = str + char(0);
        int N = n + 1;
        vector<int> p(N), c(N);
        int alphabet = 256;
        vector<int> cnt(max(alphabet, N), 0);
        for(int i = 0; i < N; i++) {
            cnt[(unsigned char)t[i]]++;
        }
        for(int i = 1; i < alphabet; i++) {
            cnt[i] += cnt[i - 1];
        }
        for(int i = 0; i < N; i++) {
            p[--cnt[(unsigned char)t[i]]] = i;
        }
        c[p[0]] = 0;
        int classes = 1;
        for(int i = 1; i < N; i++) {
            if(t[p[i]] != t[p[i - 1]]) {
                classes++;
            }
            c[p[i]] = classes - 1;
        }
        vector<int> pn(N), cn(N);
        for(int h = 0; (1 << h) < N; h++) {
            int step = 1 << h;
            for(int i = 0; i < N; i++) {
                pn[i] = p[i] - step;
                if(pn[i] < 0) {
                    pn[i] += N;
                }
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for(int i = 0; i < N; i++) {
                cnt[c[pn[i]]]++;
            }
            for(int i = 1; i < classes; i++) {
                cnt[i] += cnt[i - 1];
            }
            for(int i = N - 1; i >= 0; i--) {
                p[--cnt[c[pn[i]]]] = pn[i];
            }
            cn[p[0]] = 0;
            int newClasses = 1;
            for(int i = 1; i < N; i++) {
                pair<int, int> cur = {c[p[i]], c[(p[i] + step) % N]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + step) % N]};
                if(cur != prev) {
                    newClasses++;
                }
                cn[p[i]] = newClasses - 1;
            }
            c.swap(cn);
            classes = newClasses;
        }
        int k = 0;
        for(int i = 0; i < N; i++) {
            if(p[i] == n) {
                continue;
            }
            sa[++k] = p[i] + 1;
        }
        for(int i = 1; i <= n; i++) {
            rk[sa[i]] = i;
        }
        k = 0;
        for(int i = 0; i < n; i++) {
            int pos = rk[i + 1];
            if(pos == 1) {
                k = 0;
                continue;
            }
            int j = sa[pos - 1] - 1;
            while(i + k < n && j + k < n && str[i + k] == str[j + k]) {
                k++;
            }
            height[pos] = k;
            if(k) {
                k--;
            }
        }
    }
};
