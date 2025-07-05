#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    string s, t;
    cin >> s >> t;
    int n = s.size(), m = t.size();
    vector<int> pres(n + 1), pret(m + 1);
    for(int i = 1; i <= n; i++) {
        pres[i] = pres[i - 1] + (s[i - 1] == 'A' ? 1 : 2);
    }
    for(int i = 1; i <= m; i++) {
        pret[i] = pret[i - 1] + (t[i - 1] == 'A' ? 1 : 2);
    }
    int q;
    cin >> q;
    while(q--) {
        int a, b, x, y;
        cin >> a >> b >> x >> y;
        int u = pres[b] - pres[a - 1];
        int v = pret[y] - pret[x - 1];
        if(u % 3 == v % 3) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
