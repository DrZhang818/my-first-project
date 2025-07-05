#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve(){ 
    int cur;
    char c;
    cin >> cur;
    int ans = 0;
    int pre = cur;
    bool neg = false;
    while(cin >> c && c != '=') {
        cin >> cur;
        if(c == '+') {
            ans += (neg ? -1 : 1) * pre;
            pre = cur;
            neg = false;
        } 
        else if(c == '-') {
            ans += (neg ? -1 : 1) * pre;
            pre = cur;
            neg = true;
        }
        else if(c == '*') {
            pre *= cur;
        }
        else if(c == '/') {
            pre /= cur;
        }
    }
    ans += (neg ? -1 : 1) * pre;
    cout << ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

