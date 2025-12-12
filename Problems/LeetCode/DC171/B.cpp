#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

bool ck(int x) {
    string s;
    while(x) s += '0' + x % 10, x /= 10;
    string t = s;
    reverse(s.begin(), s.end());
    return s == t;
}
set<int> st;
int init = []() {
    st.insert(0);
    int i = 1;
    while(*st.rbegin() <= 5000) {
        if(ck(i)) st.insert(i);
        i++;
    }
} ();

class Solution {
public:
    vector<int> minOperations(vector<int>& a) {
        for(int &x : a) {
            auto it = st.lower_bound(x);
            x = abs(x - *it);
            it = prev(it);
            x = min(x, abs(x - *it));
        }
        return a;
    }
};