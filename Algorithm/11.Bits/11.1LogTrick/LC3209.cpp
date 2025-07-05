#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    ll countSubarrays(vector<int>& a, int k) {
        int n = a.size();
        ll ans = 0, cnt = 0;
        for(int i = 0; i < n; i++) {
            int v = a[i];
            if(v == k) {
                cnt++;
            }
            for(int j = i - 1; j >= 0 && (a[j] & a[i]) != a[j]; j--) {
                if(a[j] == k) {
                    cnt--;
                }
                a[j] &= a[i];
                if(a[j] == k) {
                    cnt++;
                }
            }
            ans += cnt;
        }
        return ans;
    }
};