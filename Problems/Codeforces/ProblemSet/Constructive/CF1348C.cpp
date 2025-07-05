#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    string s;
    cin >> n >> k >> s;
    sort(s.begin(), s.end());
    if(k == 1) {
        cout << s << "\n";
        return;
    }
    if(s[k - 1] != s[0]) {
        cout << s[k - 1] << "\n";
        return;
    }
    string ans;
    if(s[k] == s[n - 1]) {
        cout << s[0];
        for(int i = k; i < n; i += k) {
            cout << s[i];
        }
        cout << "\n";
    } else {
        for(int i = k - 1; i < n; i++) {
            cout << s[i];
        }
        cout << "\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
