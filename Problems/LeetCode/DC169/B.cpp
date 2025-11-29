#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int countMajoritySubarrays(vector<int>& a, int k) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            int c = 0;
            for(int j = i; j >= 0; j--) {
                if(a[j] == k) {
                    c++;
                }
                if(2 * c > i - j + 1) {
                    ans++;
                }
            }
        }
        return ans;
    }
};