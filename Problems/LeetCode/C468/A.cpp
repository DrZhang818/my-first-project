#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int evenNumberBitwiseORs(vector<int>& a) {
        int ora = 0;
        for(int x : a) {
            if(x % 2 == 0) {
                ora |= x;
            }
        }
        return ora;
    }
};