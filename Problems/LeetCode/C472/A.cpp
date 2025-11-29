#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int missingMultiple(vector<int>& a, int k) {
        vector<bool> vis(201);
        for(int x : a) vis[x] = true;
        for(int i = k; ; i += k) {
            if(!vis[i]) {
                return i;
            }
        }
        return -1;
    }
};