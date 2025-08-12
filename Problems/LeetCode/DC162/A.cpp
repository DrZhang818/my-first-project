#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int earliestFinishTime(vector<int>& a, vector<int>& at, vector<int>& b, vector<int>& bt) {
        int ans = inf;
        int mn = inf;
        for(int i = 0; i < a.size(); i++) {
            mn = min(mn, a[i] + at[i]);
        }
        for(int i = 0; i < b.size(); i++) {
            ans = min(ans, max(b[i], mn) + bt[i]);
        }
        mn = inf;
        for(int i = 0; i < b.size(); i++) {
            mn = min(mn, b[i] + bt[i]);
        }
        for(int i = 0; i < a.size(); i++) {
            ans = min(ans, max(a[i], mn) + at[i]);
        }
        return ans;
    }
};