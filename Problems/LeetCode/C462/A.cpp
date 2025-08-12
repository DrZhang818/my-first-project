#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& a, int x, int y, int k) {
        for(int l = x, r = x + k - 1; l < r; l++, r--) {
            for(int j = y; j < y + k; j++) {
                swap(a[l][j], a[r][j]);
            }
        }
        return a;
    }
};