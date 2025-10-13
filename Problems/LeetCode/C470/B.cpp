#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int longestSubsequence(vector<int>& a) {
        bool ok = false;
        int sum = 0;
        for(int x : a) {
            if(x) {
                ok = true;
            }
            sum ^= x;
        }
        if(!ok) {
            return 0;
        }
        if(sum == 0) {
            return a.size() - 1;
        } 
        return a.size();
    }
};