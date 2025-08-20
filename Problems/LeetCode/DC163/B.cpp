#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll perfectPairs(vector<int>& a) {
        for(int &x : a) {
            x = abs(x);
        }
        sort(a.begin(), a.end());
        ll ans = 0;
        for(int i = 0, j = 0; i < a.size(); i++) {
            while(2 * a[j] < a[i]) {
                j++;
            }
            ans += i - j;
        }
        return ans;
    }
};