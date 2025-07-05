#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class Solution {
public:
    int maxDifference(string s) {
        unordered_map<char,int> mp;
        for(char c : s) mp[c]++;
        int even = INT_MAX, odd = -1;
        for(auto [_,c] : mp){
            if(c % 2 == 0) even = min(even, c);
            else odd = max(odd, c);
        }
        return oodd
    }
};