#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

int Hash(vector<int> &a) {
    int res = 0;
    for(int x : a) {
        res = res << 3 | x;
    }
    return res;
}

class Solution {
public:
    int minSplitMerge(vector<int>& a, vector<int>& b) {
        if(a == b) {
            return 0;
        }
        int n = a.size();
        vector<int> val;
        for(int x : a) {
            val.push_back(x);
        }
        sort(val.begin(), val.end());
        for(int &x : a) {
            x = lower_bound(val.begin(), val.end(), x) - val.begin() + 1;
        }
        for(int &x : b) {
            x = lower_bound(val.begin(), val.end(), x) - val.begin() + 1;
        }
        unordered_map<int, int> dis;
        dis[Hash(a)] = 0;
        queue<vector<int>> q;
        q.emplace(a);
        while(!q.empty()) {
            auto cur = q.front(); q.pop();
            int d = dis[Hash(cur)];
            for(int l = 0; l < n; l++) {
                for(int r = l; r < n; r++) {
                    for(int k = 0; k < l; k++) {
                        vector<int> nxt;
                        for(int p = 0; p < k; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = l; p <= r; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = k; p < l; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = r + 1; p < n; p++) {
                            nxt.push_back(cur[p]);
                        }
                        if(dis.contains(Hash(nxt))) {
                            continue;
                        }
                        dis[Hash(nxt)] = d + 1;
                        if(nxt == b) {
                            return d + 1;
                        }
                        q.emplace(nxt);
                    }
                    for(int k = r + 1; k < n; k++) {
                        vector<int> nxt;
                        for(int p = 0; p < l; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = r + 1; p <= k; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = l; p <= r; p++) {
                            nxt.push_back(cur[p]);
                        }
                        for(int p = k + 1; p < n; p++) {
                            nxt.push_back(cur[p]);
                        }
                        if(dis.contains(Hash(nxt))) {
                            continue;
                        }
                        dis[Hash(nxt)] = d + 1;
                        if(nxt == b) {
                            return d + 1;
                        }
                        q.emplace(nxt);
                    }
                }
            }
        }
        return -1;
    }
};