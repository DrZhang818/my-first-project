#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/contest/1956/problem/C
void solve() {
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    ll tot = 0;
    for(int i = 1; i <= n; i++) {
        tot += (2 * i - 1) * i;
    }    
    cout << tot << " " << 2 * n - 1 << "\n";
    for(int i = 2 * n - 1; i >= 1; i--) {
        cout << (i % 2 == 1 ? 1 : 2) << " " << (i + 1) / 2 << " ";
        for(int j = 1; j <= n; j++) {
            cout << j << " \n"[j == n];
        }
    }
}    

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
