#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = 5E4 + 5;
vector<int> minp(N), primes;
auto init = []() -> int {
    for(int i = 2; i < N; i++) {
        if(!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for(auto p : primes) {
            if(i * p >= N) break;
            minp[i * p] = p;
            if(minp[i * p] == i) break;
        }
    }
    return 0;
}();

class Solution {
public:
    int primeSubarray(vector<int>& a, int k) {
        int n = a.size();
        map<int,int> mp;
        vector<int> q(n + 1);
        int l = 0, r = 0, ans = 0;
        for(int i = 0, L = 0; i < n; i++) {
            if(minp[a[i]] == a[i]) {
                q[r++] = i;
                mp[a[i]]++;
            }
            while(!mp.empty() && mp.rbegin()->first - mp.begin()->first > k) {
                if(minp[a[L]] == a[L]) {
                    if(--mp[a[L]] == 0) {
                        mp.erase(a[L]);
                    }
                    l++;
                }
                L++;
            }
            if(r - l >= 2) {
                ans += q[r - 2] - L + 1;
            }
        }
        return ans;
    }
};