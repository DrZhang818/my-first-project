#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        if(num * 9 < sum) {
            return "";
        }
        string ans(num, '0');
        for(int i = 0; i < num && sum; i++) {
            ans[i] = min(9, sum);
            sum -= min(9, sum);
        }
        return ans;
    }
};