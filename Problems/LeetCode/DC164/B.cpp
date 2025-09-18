#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int score(vector<string>& s, char x) {
        vector<int> c1(26), c2(26);
        int c3 = 0;
        for(auto t : s) {
            if(t[0] == x && t[1] == x) {
                c3++;
            } else if(t[0] == x) {
                c1[t[1] - 'a']++;
            } else if(t[1] == x) {
                c2[t[0] - 'a']++;
            }
        }
        sort(c1.begin(), c1.end(), greater<int>());
        sort(c2.begin(), c2.end(), greater<int>());
        int s1 = accumulate(c1.begin(), c1.end(), 0);
        int s2 = accumulate(c2.begin(), c2.end(), 0);
        int ans = 0;
        for(int c = 0; c <= c3; c++) {
            int t1 = s1 + c;
            int t2 = s2 + c3 - c;
            int cur = 0;
            int mx1 = max(c1[0], c);
            int mx2 = max(c2[0], c3 - c);
            if(mx1 * 2 > t1) {
                cur += t1 - mx1;
            } else {
                cur += t1 / 2;
            }
            if(mx2 * 2 > t2) {
                cur += t2 - mx2;
            } else {
                cur += t2 / 2;
            }
            ans = max(ans, cur);
        }
        return ans;
    }
};