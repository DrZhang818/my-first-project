#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1E15;

class Solution {
public:
    int minStable(vector<int>& a, int k) {
        int n = a.size();
        auto ck = [&](int x) -> bool {
            auto b = a;
            int l = 0, len = 0, cnt = 0;
            for(int i = 0; i < n; i++) {
                int j = i - 1;
                for(; j >= 0 && gcd(b[i], b[j]) != b[j]; j--) {
                    b[j] = gcd(b[i], b[j]);
                }
                while(l <= i && b[l] == 1) l++;
                len = i - l + 1;
                if(len > x) {
                    b[i] = 1;
                    cnt++;
                    l = i + 1;
                }
            }
            return cnt <= k;
        };
        int l = -1, r = n + 1;
        while(l + 1 < r) {
            int mid = l + r >> 1;
            if(ck(mid)) {
                r = mid;
            } else {
                l = mid;
            }
        }
        return r;
    }
};