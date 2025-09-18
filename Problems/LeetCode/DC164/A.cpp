#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int getLeastFrequentDigit(int n) {
        array<int,10> a;
        while(n) {
            a[n % 10]++;
            n /= 10;
        }
        int c = 0;
        for(int i = 0; i < 10; i++) {
            if(a[i] < a[c]) {
                c = i;
            }
        }
        return c;
    }
};