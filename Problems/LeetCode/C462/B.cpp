#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int sortPermutation(vector<int>& a) {
        int n = a.size();
        if(a[0] != 0) {
            return 0;
        }
        int ans = (1 << 30) - 1;
        for(int i = 0; i < n; i++) {
            if(a[i] == i) continue;
            ans &= a[i] & i;
        }
        return ans == inf ? 0 : ans;
    }
};