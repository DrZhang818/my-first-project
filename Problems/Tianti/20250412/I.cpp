#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, m, lim;
    cin >> n >> m >> lim;
    vector<queue<char>> q(n + 1);
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            q[i].push(c);
        }
    }
    stack<char> stk;
    vector<char> ans;
    int op;
    while(cin >> op) {
        if(op == -1) break;
        if(op == 0) {
            if(stk.empty()) continue;
            ans.push_back(stk.top());
            stk.pop();
        } else {
            if(q[op].empty()) continue;
            if(stk.size() == lim) {
                ans.push_back(stk.top());
                stk.pop();
            }
            stk.push(q[op].front());
            q[op].pop();
        }
    }
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i];
        if(i == ans.size() - 1) cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
