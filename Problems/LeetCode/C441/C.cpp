#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
class Solution {
public:
    int minZeroArray(vector<int>& a, vector<vector<int>>& Q) {
        int n = a.size(), q = Q.size();
        int k = -1;
        bool ck = true;
        for(int i = 0; i < n; i++) {
            if(a[i]) ck = false;
        }
        if(ck) {
            return 0;
        }
        vector<set<ll>> mp(n + 1);
        for(int i = 0; i < n; i++) {
            mp[i].insert(0);
        }
        queue<ll> qq;
        for(int i = 0; i < q; i++) {
            int l = Q[i][0], r = Q[i][1], x = Q[i][2];
            for(int j = l; j <= r; j++) {
                for(auto c : mp[j]) {
                    qq.push(c);
                }             
                while(!qq.empty()) {
                    mp[j].insert(qq.front() + x);
                    qq.pop();
                }   
            }
            bool ok = true;
            for(int j = 0; j < n; j++) {
                if(!mp[j].count(a[j])) {
                    ok = false;
                    break;
                }
            }
            if(ok) {
                k = i + 1;
                break;
            }
        }
        return k;
    }
};