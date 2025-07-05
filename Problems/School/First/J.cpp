#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    ll x = 0, y;
    y = n - 2;
    auto work = [&](int p) -> int {
        int t = n, res = 0;
        while(t) {
            res += t % p;
            t /= p;
        }
        return res;
    };
    for(int p = 2; p <= n - 1; p++) {
        x += work(p);
    }
    ll g = __gcd(x, y);
    x /= g;
    y /= g;
    cout << x << "/" << y << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
