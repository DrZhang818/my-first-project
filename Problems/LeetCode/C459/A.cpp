#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    bool checkDivisibility(int n) {
        int a = 0, b = 1, x = n;
        while(x) {
            int pop = x % 10;
            x /= 10;
            a += pop;
            b *= pop;
        }
        return n % (a + b) == 0;
    }
};