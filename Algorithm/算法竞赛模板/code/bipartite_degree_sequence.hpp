#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
// Gale–Ryser 构造：逐行取剩余度数最大的若干列（按剩余度分组，从组内右侧取）
struct BiDegree {
    static bool run(int n, int m, const vector<int>& row, const vector<int>& col,
                    vector<vector<int>>& mat) {
        mat.assign(n + 1, vector<int>(m + 1, 0));
        vector<int> csum(m + 1);
        i64 total = 0;
        for(int i = 1; i <= n; i++) {
            if(row[i] < 0 || row[i] > m) {
                return false;
            }
            total += row[i];
        }
        for(int j = 1; j <= m; j++) {
            if(col[j] < 0 || col[j] > n) {
                return false;
            }
            csum[j] = col[j];
            total -= col[j];
        }
        if(total != 0) {
            return false;
        }
        vector<int> ord(m);
        iota(ord.begin(), ord.end(), 1);
        sort(ord.begin(), ord.end(), [&](int a, int b) { return csum[a] > csum[b]; });
        for(int i = 1; i <= n; i++) {
            int cnt = row[i];
            for(int lo = 0, hi = 0; lo < m && cnt > 0; lo = hi) {
                if(csum[ord[lo]] == 0) {
                    break;
                }
                while(hi < m && csum[ord[hi]] == csum[ord[lo]]) {
                    hi++;
                }
                for(int k = hi - 1; k >= lo && cnt > 0; k--) {
                    mat[i][ord[k]] = 1;
                    csum[ord[k]]--;
                    cnt--;
                }
            }
            if(cnt > 0) {
                return false;
            }
        }
        for(int j = 1; j <= m; j++) {
            if(csum[j] != 0) {
                return false;
            }
        }
        return true;
    }
};
