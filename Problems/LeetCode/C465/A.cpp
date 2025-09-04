#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    vector<int> recoverOrder(vector<int>& a, vector<int>& b) {
        int n = a.size();
        vector<int> vis(n + 1);
        for(int x : b) {
            vis[x] = true;
        }
        vector<int> ans;
        for(int x : a) {
            if(vis[x]) {
                ans.push_back(x);
            }
        }
        return ans;
    }
};