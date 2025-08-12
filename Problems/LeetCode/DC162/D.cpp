#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://leetcode.cn/problems/threshold-majority-queries/description/
struct info {
    int bid, l, r, x, qid;
    friend bool operator < (const info &a, const info &b) {
        if(a.bid != b.bid) return a.bid < b.bid;
        return a.r < b.r;
    }
};
class Solution {
public:
    vector<int> subarrayMajority(vector<int>& a, vector<vector<int>>& query) {
        int n = a.size(), m = query.size();
        unordered_map<int,int> cnt;
        int cmx = 0, mn = 0;
        auto add = [&](int x) {
            int c = ++cnt[x];
            if(c > cmx) {
                cmx = c;
                mn = x;
            } else if(c == cmx) {
                mn = min(mn, x);
            }
        };
        vector<int> ans(m, -1);
        int block = ceil(n / sqrt(m * 2));
        vector<info> Q;
        for(int i = 0; i < m; i++) {
            int l = query[i][0], r = query[i][1] + 1, x = query[i][2];
            if(r - l > block) {
                Q.emplace_back(l / block, l, r, x, i);
                continue;
            }
            for(int j = l; j < r; j++) {
                add(a[j]);
            }
            if(cmx >= x) {
                ans[i] = mn;
            }
            cnt.clear();
            cmx = 0;
        }
        sort(Q.begin(), Q.end());
        for(int i = 0, R; i < Q.size(); i++) {
            auto [bid, l, r, x, qid] = Q[i];
            int l0 = (bid + 1) * block;
            if(i == 0 || bid != Q[i - 1].bid) {
                R = l0;
                cnt.clear();
                cmx = 0;
            }
            for(; R < r; R++) {
                add(a[R]);
            }
            int tcmx = cmx, tmn = mn;
            for(int j = l; j < l0; j++) {
                add(a[j]);
            }
            if(cmx >= x) {
                ans[qid] = mn;
            }
            cmx = tcmx;
            mn = tmn;
            for(int j = l; j < l0; j++) {
                cnt[a[j]]--;
            }
        }
        return ans;
    }
};