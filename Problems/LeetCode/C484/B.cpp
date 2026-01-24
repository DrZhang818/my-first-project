#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int centeredSubarrays(vector<int>& a) {
        int n = a.size();
        int ans = 0;
        for(int i = 0; i < n; i++) {
            set<int> st;
            int sum = 0;
            for(int j = i; j >= 0; j--) {
                sum += a[j];
                st.insert(a[j]);
                if(st.contains(sum)) {
                    ans++;
                }
            }
        }
        return ans;
    }
};