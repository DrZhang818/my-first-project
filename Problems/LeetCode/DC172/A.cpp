#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

class Solution {
public:
    int minOperations(vector<int>& a) {
        int ans = 0;
        int n = a.size();
        set<int> st;
        int R = -1;
        for(int i = n - 1; i >= 0; i--) {
            if(st.contains(a[i])) {
                R = i;
                break;
            }
            st.insert(a[i]);
        }      
        return (R + 3) / 3;
    }
};