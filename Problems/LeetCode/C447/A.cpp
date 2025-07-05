#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int l, r;
};
class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& a) {
        vector<info> r(n + 1, {inf,-inf}), c(n + 1,{inf,-inf});
        for(auto p : a) {
            int x = p[0], y = p[1];
            r[x].l = min(r[x].l, y), r[x].r = max(r[x].r, y);
            c[y].l = min(c[y].l, x), c[y].r = max(c[y].r, x);
        }
        int ans = 0;
        for(auto p : a) {
            int x = p[0], y = p[1];
            if(r[x].l < y && y < r[x].r && c[y].l < x && x < c[y].r) {
                ans++;
            }
        }
        return ans;
    }
};