#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



class Solution {
public:
    const db eps = 1e5;
    db separateSquares(vector<vector<int>>& a) {
        sort(a.begin(), a.end(), [](auto &a, auto &b) -> bool{
            return a[1] < b[1];
        });
        int n = a.size();
        db mn = a[0][1], mx = a[n - 1][1] + a[n - 1][2];
        db l = mn, r = mx;
        auto check = [&](db x) -> bool {
            db s1 = 0, s2 = 0;
            for(int i = 0; i < n; i++) {
                if(a[i][1] + a[i][2] < x) {
                    s1 += a[i][2] * a[i][2];
                } else if(a[i][1] >= x) {
                    s2 += a[i][2] * a[i][2];
                } else {
                    s1 += a[i][2] * (x - a[i][1]);
                    s2 += a[i][2] * (a[i][1] + a[i][2] - x);
                }
            }
            return s2 <= s1;
        };
        while(r - l >= eps) {
            db mid = (l + r) / 2;
            if(check(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r;
    }
};