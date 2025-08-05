#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minTime(string s, vector<int>& ord, int k) {
        int n = s.size();
        auto ck = [&](int x) -> bool {
            vector<int> a(n);
            for(int i = 0; i < x; i++) {
                a[ord[i]] = 1;
            }
            int l = -1, cnt = 0;
            for(int i = 0; i < n; i++) {
                if(a[i]) l = i;
                cnt += l + 1;
            }
            return cnt >= k;
        };
        int l = -1, r = n;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r == n ? -1 : r;
    }
};