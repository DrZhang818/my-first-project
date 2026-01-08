#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int maximumSum(vector<int>& a) {
        array<vector<int>, 3> adj;
        for(int x : a) {
            adj[x % 3].push_back(x);
        }      
        int ans = 0;
        for(int i = 0; i < 3; i++) {
            sort(adj[i].begin(), adj[i].end(), greater<int>());
            if(adj[i].size() >= 3) {
                ans = max(ans, adj[i][0] + adj[i][1] + adj[i][2]);
            }
        }
        if(!adj[0].empty() && !adj[1].empty() && !adj[2].empty()) {
            ans = max(ans, adj[0][0] + adj[1][0] + adj[2][0]);
        }
        return ans;
    }
};