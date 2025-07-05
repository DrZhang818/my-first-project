#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


//https://leetcode.cn/problems/find-all-people-with-secret/
class DSU{
private:
    vector<int> fa, sec;
public:
    DSU () {}
    DSU (int n) {
        fa.resize(n);
        iota(fa.begin(), fa.end(), 0);
        sec.assign(n, 0);
        sec[0] = 1;
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
        sec[x] |= sec[y];
        fa[y] = x;
        return true;
    }
    bool is_sec(int x) {
        return sec[find(x)];
    }
    void reset(int x) {
        fa[x] = x;
    }
};
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        map<int, vector<PII>> mp;
        
        for(int i = 0; i < meetings.size(); i++) {
            mp[meetings[i][2]].emplace_back(meetings[i][0], meetings[i][1]);
        } 
        DSU g(n);
        vector<int> ans;
        ans.reserve(n);  
        g.merge(0, firstPerson);
        for(auto &[_, vec] : mp) {
            for(auto [x, y] : vec) {
                g.merge(x, y);
            }
            for(auto [x, y] : vec) {
                if(!g.is_sec(x)) {
                    g.reset(x);
                    g.reset(y);
                }
            }
        }
        for(int i = 0; i < n; i++) {
            if(g.is_sec(i)) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};