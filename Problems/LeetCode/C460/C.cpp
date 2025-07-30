#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1000000;
vector<int> minp, primes;
auto init = []() {
    minp.resize(N + 5);
    for(int i = 2; i <= N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p > N) break;
            minp[i * p] = p;
            if(minp[i] == p) break;
        }
    }
    return 0;
}();
class Solution {
public:
    int minJumps(vector<int>& a) {
        int n = a.size();
        unordered_map<int,vector<int>> adj;
        for(int i = 0; i < n; i++) {
            int x = a[i];
            while(x != 1) {
                int p = minp[x];
                adj[p].push_back(i);
                while(x % p == 0) x /= p;
            }
        }
        vector<int> dis(n, inf);
        dis[0] = 0;
        queue<int> q;
        q.push(0);
        while(!q.empty()) {
            int u = q.front(); q.pop();
            if(u == n - 1) break;
            if(dis[u + 1] == inf) {
                dis[u + 1] = dis[u] + 1;
                q.push(u + 1);
            }
            if(u >= 2 && dis[u - 1] == inf) {
                dis[u - 1] = dis[u] + 1;
                q.push(u - 1);
            }
            if(minp[a[u]] == a[u]) {
                for(int v : adj[a[u]]) {
                    if(dis[v] == inf) {
                        dis[v] = dis[u] + 1;
                        q.push(v);
                    }
                }
                adj.erase(a[u]);
            }
        }
        return dis[n - 1];
    }
};