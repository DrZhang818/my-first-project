#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    auto check = [&](int x, int n) -> bool {
        int p1 = 0;
        for(int i = 0; i < n; i++) {
            int pop = x % 10;
            x /= 10;
            if(i < n / 2) {
                p1 += pop;
            } else {
                p1 -= pop;
            }
        }
        return p1 == 0;
    };
    ll ans = 0;
    for(int i = 1; i <= 7; i += 2) {
        for(int j = pow(10, i); j < pow(10, i + 1); j++) {
            if(check(j, i + 1)) {
                ans += 1;
                if(ans < 100) cerr << j << "\n";
            }
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

