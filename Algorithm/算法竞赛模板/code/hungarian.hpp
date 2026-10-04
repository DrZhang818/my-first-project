#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Hungarian {
    static pair<i64, vector<int>> maximum(const vector<vector<i64>>& weight) {
        int n = int(weight.size()) - 1;
        int m = n ? int(weight[1].size()) - 1 : 0;
        if(n == 0 || m == 0) {
            return {0, vector<int>(n + 1)};
        }
        if(n <= m) {
            return solve(weight);
        }
        vector<vector<i64>> transposed(m + 1, vector<i64>(n + 1));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                transposed[j][i] = weight[i][j];
            }
        }
        auto [value, columnToRow] = solve(transposed);
        vector<int> rowToColumn(n + 1);
        for(int column = 1; column <= m; column++) {
            rowToColumn[columnToRow[column]] = column;
        }
        return {value, rowToColumn};
    }

  private:
    static pair<i64, vector<int>> solve(const vector<vector<i64>>& weight) {
        int n = int(weight.size()) - 1;
        int m = int(weight[1].size()) - 1;
        const i64 inf = numeric_limits<i64>::max() / 4;
        vector<i64> u(n + 1), v(m + 1);
        vector<int> match(m + 1), previous(m + 1);
        for(int row = 1; row <= n; row++) {
            match[0] = row;
            int column = 0;
            vector<i64> slack(m + 1, inf);
            vector<bool> used(m + 1);
            do {
                used[column] = true;
                int row = match[column];
                i64 delta = inf;
                int nxt = 0;
                for(int j = 1; j <= m; j++) {
                    if(used[j]) {
                        continue;
                    }
                    i64 current = -weight[row][j] - u[row] - v[j];
                    if(current < slack[j]) {
                        slack[j] = current;
                        previous[j] = column;
                    }
                    if(slack[j] < delta) {
                        delta = slack[j];
                        nxt = j;
                    }
                }
                for(int j = 0; j <= m; j++) {
                    if(used[j]) {
                        u[match[j]] += delta;
                        v[j] -= delta;
                    } else {
                        slack[j] -= delta;
                    }
                }
                column = nxt;
            } while(match[column] != 0);
            do {
                int nxt = previous[column];
                match[column] = match[nxt];
                column = nxt;
            } while(column != 0);
        }
        vector<int> mate(n + 1);
        for(int column = 1; column <= m; column++) {
            if(match[column]) {
                mate[match[column]] = column;
            }
        }
        i64 value = 0;
        for(int row = 1; row <= n; row++) {
            value += weight[row][mate[row]];
        }
        return {value, mate};
    }
};
