#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    ll maxProfit(vector<int>& a, vector<int>& b, int k) {
        int n = a.size();
        a.insert(a.begin(), 0);
        b.insert(b.begin(), 0);
        ll Lsum = 0, Msum = 0, Rsum = 0;
        for(int i = 1; i <= n; i++) {
            Rsum += a[i] * b[i];
        }
        ll ans = Rsum;
        for(int i = 0; i <= n; i++) {
            Rsum -= a[i] * b[i];
            if(i >= k) {
                Lsum += a[i - k] * b[i - k];
            }
            Msum += a[i];
            if(i >= k / 2) {
                Msum -= a[i - k / 2];
            }
            if(i >= k) {
                ans = max(ans, Lsum + Msum + Rsum);
            }
        }
        return ans;
    }
};