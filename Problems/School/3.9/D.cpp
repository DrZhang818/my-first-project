#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    string s;
    cin >> s;
    int n = s.size();
    vector<int> ans(n);
    int c1 = 0, c2 = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'R') {
            c1 += (i % 2 == 0);
            c2 += (i % 2 == 1);
        } else {
            ans[i] += (i % 2 == 0 ? c1 : c2);
            ans[i - 1] += (i % 2 == 0 ? c2 : c1);
            c1 = c2 = 0;
        }
    }
    c1 = c2 = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == 'L') {
            c1 += (i % 2 == 0);
            c2 += (i % 2 == 1);
        } else {
            ans[i] += (i % 2 == 0 ? c1 : c2);
            ans[i + 1] += (i % 2 == 0 ? c2 : c1);
            c1 = c2 = 0;
        }
    }
    for(int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }

}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
