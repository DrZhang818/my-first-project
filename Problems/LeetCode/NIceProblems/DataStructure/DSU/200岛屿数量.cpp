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
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size();
        int ans = n * m;
        DSU g(n * m);
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(grid[i][j] == '0'){
                    ans -= 1;
                }
                else{
                    if(i > 0){
                        if(grid[i - 1][j] == '1') {
                            if(g.merge((i - 1) * n + j, i * n + j)){
                                ans -= 1;
                            }
                        }
                    }
                    if(j > 0) {
                        if(grid[i][j - 1] == '1'){
                            if(g.merge(i * n + j - 1, i * n + j)) {
                                ans -= 1;
                            }
                        }
                    }
                }
            }
        }
        return ans;
    }
};