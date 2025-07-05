#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    int idx = 1, ans = 0;
    stack<int> stk;
    for(int i = 0; i < 2 * n; i++) {
        string s;
        cin >> s;
        if(s == "add") {
            int x;
            cin >> x;
            stk.push(x);
        } else {
            if(!stk.empty() && stk.top() == idx) {
                stk.pop();
            } else if(!stk.empty()) {
                while(!stk.empty()) stk.pop();
                ans++;
            }
            idx++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
