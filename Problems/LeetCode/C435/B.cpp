#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


class Solution {
public:
    int maxDistance(string s, int k) {
        int n = s.size();
        unordered_map<char,int> mp;
        int ans = 0;
        int dx = 0, dy = 0;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == 'N' || s[i] == 'S'){
                dy += (s[i] == 'N' ? 1 : -1);
            }
            else {
                dx += (s[i] == 'E' ? 1 : -1);
            }
            mp[s[i]]++;
            int x = abs(dx), y = abs(y), t = k;
            if(dx > 0){
                x += min(t,mp['W']);
                t -= min(t,mp['W']);
            }else{
                x += min(t,mp['E']);
                t -= min(t,mp['E']);
            }
            if(dy > 0){
                y += min(t,mp['S']);
                t -= min(t,mp['S']);
            }else{
                y += min(t,mp['N']);
                t -= min(t,mp['N']);
            }
            ans = max(ans, x + y);
        }
        return ans;
    }
};