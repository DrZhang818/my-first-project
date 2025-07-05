#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minSwaps(vector<int>& a) {
        int c0 = 0, c1 = 0;
        for(int x : a) {
            c0 += x % 2 == 0;
            c1 += x % 2 == 1;
        }
        auto get = [&](int st) -> int {
            int res = 0, idx = st;
            for(int i = 0; i < a.size(); i++) {
                if(a[i] % 2 == 0) {
                    res += abs(i - idx);
                    idx += 2; 
                }
            }
            return res;
        };
        int ans = -1;
        if(c0 == c1 + 1 || c1 == c0 + 1) {
            ans = get(c1 == c0 + 1);            
        } else if(c0 == c1) {
            ans = min(get(0), get(1));
        }
        return ans;
    }
};