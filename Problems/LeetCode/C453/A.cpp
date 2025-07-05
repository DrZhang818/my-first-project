#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    bool canMakeEqual(vector<int>& a, int k) {
        int c1 = 0, c2 = 0, n = a.size();
        a.push_back(0);
        auto b = a;
        for(int i = 0; i < n - 1; i++) {
            if(b[i] != 1) {
                c1++;
                b[i + 1] *= -1;
            }
        }
        if(b[n - 1] != 1) c1 = inf;
        b = a;
        for(int i = 0; i < n - 1; i++) {
            if(b[i] != -1) {
                c2++;
                b[i + 1] *= -1;
            }
        }
        if(b[n - 1] != -1) c2 = inf;
        return c1 <= k || c2 <= k;
    }
};