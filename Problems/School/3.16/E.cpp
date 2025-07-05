#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


void solve() { 
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = "#" + s;
    vector<ull> H(n + 1);
    ull P = 19260817;
    for(int i = 1; i <= n; i++) {
        H[i] = H[i - 1] * P + s[i];
    }
    vector<ull> fac(n + 1);
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * P;
    }
    auto check = [&](int x) -> bool {
        map<ull, int> mp;
        for(int i = 1; i <= n - x + 1; i++) {
            ull th = H[i + x - 1] - H[i - 1] * fac[x];
            if(mp[th] != 0 && mp[th] < i) {
                return true;
            }
            if(!mp[th]) mp[th] = i + x - 1;
        }
        return false;
    };
    int l = -1, r = n;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
