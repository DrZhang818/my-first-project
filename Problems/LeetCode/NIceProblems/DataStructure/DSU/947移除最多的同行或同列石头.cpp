#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class DSU{
private:
    vector<int> fa, siz;
public:
    DSU () {}
    DSU (int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        siz.assign(n, 1);
    }
    int find(int x) {
        while(x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) {
            return false;
        }
        siz[x] += siz[y];
        fa[y] = x;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};
class Solution {
public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        int ans = 0;
        unordered_map<int,int> xs, ys;
        DSU g(n + 1);
        for(int i = 0; i < n; i++) {
            int x = stones[i][0], y = stones[i][1];
            if(xs[x] != 0) {
                if(g.merge(xs[x], i + 1)){
                    ans++;
                }
            }
            if(ys[y] != 0){
                if(g.merge(ys[y], i + 1)){
                    ans++;
                }
            }
            xs[x] = i + 1;;
            ys[y] = i + 1;
        }
        return ans;
    }
};