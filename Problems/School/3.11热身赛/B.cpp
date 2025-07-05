#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int q, n;
    cin >> q >> n;
    cin.ignore();
    while(q--) {
        string s;
        getline(cin, s);
        istringstream ss(s);
        int ans = 1, cur = 0;
        string tok;
        bool st = true;
        while(ss >> tok) {
            cur += tok.size();
            if(st) {
                st = false;
            } else {
                cur += 1;
            }
            if(cur > n) {
                ans += 1;
                cur = tok.size();
            }
        }   
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
