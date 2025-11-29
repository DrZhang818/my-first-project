#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    vector<int> lexSmallestNegatedPerm(int n, ll target) {
        vector<int> pos, neg;
        ll t = target;
        for(int i = n; i >= 1; i--) {
            ll sum = 1LL * i * (i - 1) / 2;
            if(sum >= target + i) {
                neg.push_back(i);
                target += i;
            } else {
                pos.push_back(i);
                target -= i;
            }
        }
        vector<int> ans;
        for(int i = 0; i < neg.size(); i++) {
            ans.push_back(-neg[i]);
        }
        for(int i = pos.size() - 1; i >= 0; i--) {
            ans.push_back(pos[i]);
        }
        ll sum = 0;
        for(int x : ans) {
            sum += x;
        }
        return sum == t ? ans : vector<int>();
    }
};