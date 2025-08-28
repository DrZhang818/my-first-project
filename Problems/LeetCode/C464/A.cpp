#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sa = 0, sb = 0;
        for(int i = 1; i <= 2 * n; i++) {
            if(i & 1) {
                sa += i; 
            } else {
                sb += i;
            }
        }      
        return gcd(sa, sb);
    }
};