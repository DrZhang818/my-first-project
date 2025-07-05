#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    bool checkEqualPartitions(vector<int>& a, ll k) {
        int n = a.size();
        for(int s = 0; s < 1 << n; s++) {
            ll f1 = 1, f2 = 1;
            for(int i = 0; i < n; i++) {
                if(s >> i & 1) {
                    f1 *= a[i];
                } else {
                    f2 *= a[i];
                }
                if(f1 > k || f2 > k) {
                    break;
                }
            }
            if(f1 == k && f2 == k) {
                return true;
            }
        }
        return false;
    }
};
