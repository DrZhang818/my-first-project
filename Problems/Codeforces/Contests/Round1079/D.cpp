#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;


void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;

    stack<int> stk0, stk1;
    vector<int> pos0, pos1;
    for(int i = 0; i < n; i++) {
        if(s[i] == '(') {
            stk0.push(i);
        } else if(s[i] == ')') {
            if(!stk0.empty()) {
                stk0.pop();
            } else {
                pos0.push_back(i);
            }
        } else if(s[i] == '[') {
            stk1.push(i);
        } else {
            if(!stk1.empty()) {
                stk1.pop();
            } else {
                pos1.push_back(i);
            }
        }
    }

    vector<int> p;
    for(int i : pos0) p.push_back(i);
    for(int i : pos1) p.push_back(i);
    int rem = p.size();
    while(!stk0.empty()) {
        p.push_back(stk0.top());
        stk0.pop();
    }
    while(!stk1.empty()) {
        p.push_back(stk1.top());
        stk1.pop();
    }

    sort(p.begin(), p.end());

    int ans = 0;
    int L = 0, R = 0;
    for(int i : p) {
        if(s[i] == '(' || s[i] == '[') {
            L++;
        } else {
            if(R > 0) {
                R--;
                continue;
            }
            if(rem > 1) {
                R++;
                rem -= 2;
                ans++;
            } else if(L > 0) {
                L--;
                rem--;
                ans++;
            }
        }
    }

    assert(R == 0);
    assert(rem <= 1);

    if(rem == 1) {
        ans += 2;
        L--;
    }

    ans += L / 2;

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
