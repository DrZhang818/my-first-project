#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;

class Solution {
public:
    int xorAfterQueries(vector<int>& a, vector<vector<int>>& Q) {
        int n = a.size();
        int sum = 0;
        for(int i = 0; i < n; i++) {
            sum ^= a[i];
        }
        for(int i = 0; i < Q.size(); i++) {
            int l = Q[i][0], r = Q[i][1], k = Q[i][2], v = Q[i][3];
            for(int j = l; j <= r; j += k) {
                sum ^= a[j];
                a[j] = 1LL * a[j] * v % MOD;
                sum ^= a[j];
            }
        }
        return sum;
    }
};
