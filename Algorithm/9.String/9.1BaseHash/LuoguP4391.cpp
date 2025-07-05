#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
constexpr ull P = 1000000007;
void solve() { 
    int n;
    string s;
    cin >> n >> s;
    s = "#" + s;
    vector<ull> H(n + 1), fac(n + 1);
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        H[i] = H[i - 1] * P + s[i];
        fac[i] = fac[i - 1] * P;
    }
    for(int i = 1; i <= n; i++) {
        if(H[n - i] == H[n] - H[i] * fac[n - i]) {
            cout << i << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
