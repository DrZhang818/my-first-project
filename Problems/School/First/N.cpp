#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    stack<char> stk;
    for(char c : s) {
        if(stk.empty() || c != stk.top()) {
            stk.push(c);
        } else {
            stk.pop();
        }
    }
    string ans;
    while(!stk.empty()) {
        ans += stk.top();
        stk.pop();
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
