#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    ll maximumScore(vector<int>& a, string s) {
        ll ans = 0;
        priority_queue<int> q;
        for(int i = 0; i < a.size(); i++) {
            q.push(a[i]);
            if(s[i] == '1') {
                ans += q.top();
                q.pop();
            }
        }
        return ans;
    }
};