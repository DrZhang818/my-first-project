#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000007;

void solve() {  
    string s;
    cin >> s;
    deque<char> q;
    int tag = 0;
    for(char c : s) {
        if(c == 'R') {
            tag ^= 1;
        } else {
            if(tag == 0) {
                q.push_back(c);
            } else {
                q.push_front(c);
            }
        }
    }
    stack<char> stk;
    while(!q.empty()) {
        char c;
        if(tag == 0) {
            c = q.back();
            q.pop_back();
        } else {
            c = q.front();
            q.pop_front();
        }
        if(!stk.empty() && c == stk.top()) {
            stk.pop();
        } else {
            stk.push(c);
        }
    }
    string t;
    while(!stk.empty()) {
        t += stk.top();
        stk.pop();
    }
    cout << t << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
