#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll maxTotal(vector<int>& a, vector<int>& lim) {
        int n = lim.size();
        vector<vector<int>> adj(n + 1); 
        for(int i = 0; i < n; i++) {
            adj[lim[i]].push_back(a[i]);
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            sort(adj[i].begin(), adj[i].end(), greater<int>());
            for(int j = 0; j < i && j < adj[i].size(); j++) {
                ans += adj[i][j];
            }
        }
        return ans;
    }
};