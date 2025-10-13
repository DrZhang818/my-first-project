#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int alternatingSum(vector<int>& a) {
        int ans = 0;
        for(int i = 0; i < a.size(); i++) {
            if(i & 1) {
                ans -= a[i];
            } else {
                ans += a[i];
            }
        }
        return ans;
    }
};