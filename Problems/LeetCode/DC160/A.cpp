#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    string concatHex36(int n) {
        string ans;
        vector<char> ch(36);
        for(int i = 0; i <= 9; i++) ch[i] = '0' + i;
        for(int i = 10; i <= 35; i++) ch[i] = 'A' + i - 10;
        int a = n * n;
        string t1;
        while(a) {
            t1 += ch[a % 16];
            a /= 16;
        }
        reverse(t1.begin(), t1.end());
        a = n * n * n;
        string t2;
        while(a) {
            t2 += ch[a % 36];
            a /= 36;
        }
        reverse(t2.begin(), t2.end());
        ans = t1 + t2;
        return ans;
    }
};