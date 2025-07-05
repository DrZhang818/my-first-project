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
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size(), m = strs[0].size();
        DSU g(n);
        int ans = n;
        auto check = [&](string& s, string& t) -> bool{
            int diff = 0;
            for(int i = 0; i < m && diff < 3; i++){
                diff += s[i] != t[i];
            }
            return diff == 0 || diff == 2;
        };
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(!g.same(i, j)){
                    if(check(strs[i], strs[j])){
                        g.merge(i, j);
                        ans -= 1;
                    }
                }
            }
        }
        return ans;
    }
};