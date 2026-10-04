#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct TreeDiameter {
    struct Edge {
        int to;
        i64 w;
    };
    struct Result {
        int a, b;
        i64 dis;
    };
    static Result run(const vector<vector<Edge>>& g) {
        if(g.size() <= 1) {
            return {0, 0, 0};
        }
        auto farthest = [&](int s) {
            pair<i64, int> best{0, s};
            vector<tuple<int, int, i64>> stk{{s, 0, 0}};
            while(!stk.empty()) {
                auto [u, p, d] = stk.back();
                stk.pop_back();
                best = max(best, pair{d, u});
                for(auto [v, w] : g[u]) {
                    if(v != p) {
                        stk.push_back({v, u, d + w});
                    }
                }
            }
            return best;
        };
        int a = farthest(1).second;
        auto [d, b] = farthest(a);
        return {a, b, d};
    }
};
