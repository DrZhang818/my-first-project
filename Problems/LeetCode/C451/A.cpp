#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    ll minCuttingCost(int n, int m, int k) {
        if(n <= k && m <= k) {
            return 0;
        } else {
            if(n < m) swap(n, m);
            return (ll)k * (n - k);
        }   
    }
};