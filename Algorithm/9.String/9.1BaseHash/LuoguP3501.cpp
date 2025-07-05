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
    string t = "#";
    for(int i = 1; i <= n; i++) t += (s[i] ^ 1);
    vector<ull> ps(n + 2), pt(n + 2);
    for(int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1] * P + s[i];
    }
    for(int i = n; i >= 1; i--) {
        pt[i] = pt[i + 1] * P + t[i];
    }
    vector<ull> fac(n + 1);
    fac[0] = 1;
    for(int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * P;
    }
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        int l = -1, r = min(i + 1, n - i + 1);
        while(l + 1 < r) {
            int mid = l + (r - l) / 2;
            if(ps[i] - ps[i - mid] * fac[mid] == pt[i + 1] - pt[i + mid + 1] * fac[mid]) {
                l = mid;
            } else {
                r = mid;
            }
        }
        ans += l;
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
