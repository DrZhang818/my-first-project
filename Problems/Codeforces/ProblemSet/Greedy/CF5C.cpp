#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int len = 0, cnt = 1;
    stack<pair<char,int>> stk;
    stk.push({' ', -1});
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ')') {
            if(stk.top().first == '(') {
                stk.pop();
                int j = stk.top().second;
                if(i - j > len) {
                    len = i - j;
                    cnt = 1;
                } else if(i - j == len) {
                    cnt++;
                }
            } else {
                stk.push({')', i});
            }
        } else {
            stk.push({'(', i});
        }
    }
    cout << len << " " << cnt << "\n";
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
