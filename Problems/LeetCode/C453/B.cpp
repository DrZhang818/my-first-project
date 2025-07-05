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
    int countPermutations(vector<int>& a) {
        int n = a.size();
        bool ok = true;
        for(int i = 1; i < n; i++) {
            if(a[0] >= a[i]) {
                ok = false;
                break;
            }
        }
        if(!ok) return 0;
        ll res = 1;
        for(int i = 1; i <= n - 1; i++) {
            res = res * i % MOD;
        }
        return res;
    }
};