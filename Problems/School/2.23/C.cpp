#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve1() {
    int n;
    cin >> n;
    auto check = [&](int x) {
        int i = 1;
        while(x) {
            int pop = x % 10;
            x /= 10;
            if(pop % 2 != i % 2) {
                return false;
            }
            i += 1;
        }
        return true;
    };
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(check(i)) {
            ans += 1;
        }
    }
    cout << ans << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve1();
    return 0;
}
    
