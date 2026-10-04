#pragma once
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
void floyd(vector<vector<i64>>& dis, i64 inf) {
    int n = int(dis.size()) - 1;
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            if(dis[i][k] == inf) {
                continue;
            }
            for(int j = 1; j <= n; j++) {
                if(dis[k][j] == inf) {
                    continue;
                }
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
}
