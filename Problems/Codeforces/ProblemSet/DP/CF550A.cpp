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
    vector dp(n, vector<int>(2));
    for(int i = 1; i < n; i++) {
        dp[i] = dp[i - 1];
        if(s[i] == 'A' && s[i - 1] == 'B') {
            if(i >= 3 && dp[i - 2][1]) {
                cout << "YES\n";
                return;
            }
            dp[i][0] = 1;
        } 
        if(s[i] == 'B' && s[i - 1] == 'A') {
            if(i >= 3 && dp[i - 2][0]) {
                cout << "YES\n";
                return;
            } 
            dp[i][1] = 1;
        }
    }
    cout << "NO\n";
}
// void solve() { 
//     string s;
//     cin >> s;
//     auto it1 = s.find("AB");
//     if(it1 == -1) {
//         cout << "NO\n";
//         return;
//     }
//     auto it2 = s.find("BA", it1 + 2);
//     if(it2 != -1) {
//         cout << "YES\n";
//         return;
//     }
//     it1 = s.find("BA");
//     if(it1 == -1) {
//         cout << "NO\n";
//         return;
//     }
//     it2 = s.find("AB", it1 + 2);
//     if(it2 != -1) {
//         cout << "YES\n";
//         return;
//     }
//     cout << "NO\n";
// }
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
