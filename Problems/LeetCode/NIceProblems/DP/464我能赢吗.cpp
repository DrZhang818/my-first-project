#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class Solution {
public:
    bool canIWin(int MX, int tot) {
        if(tot == 0) return true;
        if(MX * (MX + 1) / 2 < tot) return false;
        vector<int> memo(1 << MX + 1, -1);
        auto dfs = [&](this auto&& dfs, int s, int i) -> bool{
            if(i <= 0) return false;
            int &res = memo[s];
            if(res != -1) return res;
            for(int k = 0; k < MX; k++){
                if(s & (i << k) == 0){
                    if(!dfs(s | (1 << k), i - (k + 1))){
                        return res = true;
                    }
                }
            }
            return res = false;
        };
        return dfs(0, tot);
    }
};