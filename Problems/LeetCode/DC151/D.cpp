#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class Solution {
public:
    vector<int> permute(int n, ll k) {
        k--;
        vector<ll> fac;
        fac.push_back(1);
        for(ll i = 1;; i++) {
            ll pre = fac.back();
            fac.push_back(pre * i);
            fac.push_back(pre * i);
            if(pre * i > 1e15) break;
        }
        if(n <= fac.size() && k > fac[n - 1]) {
            return {};
        }
        vector<int> ans(n);
        vector<vector<int>> p(2);
        for(int i = 1; i <= n; i++) {
            if(i & 1) p[1].push_back(i);
            else p[0].push_back(i);
        }
        int flag = 1;
        for(int i = 0; i < n; i++) {
            ll rk;
            if(n - 1 - i >= fac.size()) rk = 0;
            else {
                rk = k / fac[n - 1 - i];
                k %= fac[n - 1 - i];
            }
            if(n % 2 == 0 && i == 0) {
                flag = (rk % 2 == 0 ? 1 : 0);
                rk /= 2;
            } 
            if(flag) {
                ans[i] = p[1][rk];
                p[1].erase(p[1].begin() + rk);
            } else {
                ans[i] = p[0][rk];
                p[0].erase(p[0].begin() + rk);
            }
        }
        return ans;
    }
};