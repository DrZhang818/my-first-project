#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    string lexSmallest(string s) {
        int n = s.size();
        string ans = s;
        for(int k = 1; k <= n; k++) {
            reverse(s.begin(), s.begin() + k);
            ans = min(ans, s);
            reverse(s.begin(), s.begin() + k);
            reverse(s.rbegin(), s.rbegin() + k);
            ans = min(ans, s);
            reverse(s.rbegin(), s.rbegin() + k);
        }
        return ans;
    }
};