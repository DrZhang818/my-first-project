#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int d, n;
    cin >> d >> n;
    ll ans = 0;
    auto f = [&](int x) -> int{
        int c = 0;
        while(x % 100 == 0) {
            x /= 100;
            c++;
        }
        return c;
    };
    for(int i = 0; i < n; i++) {
        if(d == 0) {
            ans += 1;
            while(f(ans) != 0) ans += 1;
        }
        else if(d == 1) {
            ans += 100;
            while(f(ans) != 1) ans += 100;
        }
        else{
            ans += 10000;
            while(f(ans) != 2) ans += 10000;
        }
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

