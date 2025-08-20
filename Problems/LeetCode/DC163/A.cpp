#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minSensors(int n, int m, int k) {
        int len = 2 * k + 1;
        return (n + len - 1) / len * ((m + len - 1) / len);
    }
};