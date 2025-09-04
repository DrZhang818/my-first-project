#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 100001;

vector<int> fac[N + 1];

auto init = []() -> int {
    for(int i = 1; i <= N; i++) {
        for(int j = i; j <= N; j += i) {
            fac[j].push_back(i);
        }
    }
    return 0;
}();

class Solution {
public:
    vector<int> minDifference(int n, int k) {
        vector<int> ans;
        vector<int> path;
        int mn = inf;
        auto dfs = [&](this auto &&self, int n, int k, int x) -> void {
            if(k == 0) {
                if(path.back() - path[0] < mn) {
                    mn = path.back() - path[0];
                    ans = path;
                }
                return;
            }
            if(k == 1) {
                if(n < x) {
                    return;
                }
                path.push_back(n);
                self(1, k - 1, n);
                path.pop_back();
            } else {
                for(int y : fac[n]) {
                    if(y < x) {
                        continue;
                    }
                    if(n / y < y) {
                        break;
                    }
                    path.push_back(y);
                    self(n / y, k - 1, y);
                    path.pop_back();
                }
            }
        };
        dfs(n, k, 1);
        return ans;
    }
};