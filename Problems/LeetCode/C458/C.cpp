#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    char processStr(string s, ll k) {
        k++;
        int n = s.size();
        vector<ll> sz(n);
        for(ll i = 0, r = 0; i < n; i++) {
            char c = s[i];
            if(isalpha(c)) r++;
            else if(c == '*') r = max(0LL, r - 1);
            else if(c == '#') r <<= 1;
            sz[i] = r;
        }
        if(sz[n - 1] < k) return '.';
        for(int i = s.size() - 1; i >= 0; i--) {
            char c = s[i];
            if(isalpha(c)) {
                if(sz[i] == k) return c;
            } else if(c == '#') {
                if(k > sz[i - 1]) k -= sz[i - 1];
            } else {
                k = sz[i] - k + 1;
            }
        }
        return '.';
    }
};