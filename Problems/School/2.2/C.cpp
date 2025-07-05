#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    auto f = [&](int x) -> int {
        int c = 0;
        while(x % 2 == 0){
            x /= 2;
            c++;
        }
        return c;
    };
    ll ans = 0;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        ans += f(x);
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

