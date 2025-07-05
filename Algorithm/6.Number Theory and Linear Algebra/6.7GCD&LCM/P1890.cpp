#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    const int MX = log2(n);
    vector<vector<int>> st(n + 1, vector<int>(MX + 1));
    for(int i = 1; i <= n; i++) st[i][0] = a[i];
    for(int s = 1; s <= MX; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {
            st[i][s] = __gcd(st[i][s - 1], st[i + (1 << s - 1)][s - 1]);
        }
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for(int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
    while(m--) {
        int l, r;
        cin >> l >> r;
        int len = lg[r - l + 1];
        cout << __gcd(st[l][len], st[r - (1 << len) + 1][len]) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
