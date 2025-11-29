#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minMoves(vector<int>& a) {
        int mx = ranges::max(a);
        int ans = 0;
        for(int x : a) {
            ans += mx - x;
        }
        return ans;
    }
};