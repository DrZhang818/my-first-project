#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    auto check = [&](int x) -> bool {
        int c = 0;
        while(x) {
            c += 1;
            x /= 10;
        }
        return (c % 2 == 1);
    };
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        ans += (check(i));
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
    
