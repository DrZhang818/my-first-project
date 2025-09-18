#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        int c = count(s.begin(), s.end(), '0');
        if(c == 0) {
            return 0;
        }
        vector<int> dis(n + 1, inf);
        dis[c] = 0;
        set<int> odd, even;
        for(int i = 1; i <= n; i++) {
            if(i & 1) {
                odd.insert(i);
            } else {
                even.insert(i);
            }
        }
        odd.insert(n + 1);
        even.insert(n + 1);
        queue<int> q;
        q.push(c);
        while(!q.empty()) {
            int a = q.front(); q.pop();
            int lo = abs(a - k), hi = min(a + k, 2 * n - a - k);
            int cur = dis[a];
            if(lo == 0) {
                return dis[a] + 1;
            }
            auto &st = lo % 2 == 1 ? odd : even;
            for(auto it = st.lower_bound(lo); *it <= hi; it = st.erase(it)) {
                dis[*it] = cur + 1;
                q.push(*it);
            }
        }
        return -1;
    }
};