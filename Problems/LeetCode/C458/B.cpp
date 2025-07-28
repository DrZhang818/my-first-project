#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

vector<int> fa;
int sz;
int find(int o){return o==fa[o]?fa[o]:fa[o]=find(fa[o]);};
void merge(int u, int v){if(find(u)!=find(v))fa[find(u)]=find(v),sz--;}
struct info{
    int u,v,w;
    friend bool operator<(const info&a,const info&b) {
        return a.w<b.w;
    }
};
class Solution {
public:
    int minCost(int n, vector<vector<int>>& e, int k) {
        fa.resize(n);
        iota(fa.begin(),fa.end(),0);
        sz=n;
        if(k==n)return 0;
        vector<info>a(n);
        for(int i=0;i<e.size();i++){
            a[i].u=e[i][0],a[i].v=e[i][1],a[i].w=e[i][2];
        }
        sort(a.begin(),a.end());
        for(auto [u,v,w]:a){
            merge(u,v);
            if(sz<=k)return w;
        }
    }
};