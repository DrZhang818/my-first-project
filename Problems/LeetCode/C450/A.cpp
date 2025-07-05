#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


class Solution {
public:
    int smallestIndex(vector<int>& a) {
        auto cal = [&](int x) -> int {
            int res = 0;
            while(x) {
                res += x % 10;
                x /= 10;
            }
            return res;
        };
        for(int i = 0; i < a.size(); i++) {
            if(cal(a[i]) == i) {
                return i;
            }
        }
        return -1;
    }
};