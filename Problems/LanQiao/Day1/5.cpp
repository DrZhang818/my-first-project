#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    auto work5 = [&](int x)->ll{
        ll c = 0;
        while(x >= 5){
            c += x / 5;
            x /= 5;
        }
        return c;
    };
    ll cnt2 = 0;
    for(int i = n; i >= n - m + 1; i--){
        int x = i;
        while(x % 2 == 0){
            cnt2++;
            x /= 2;
        }
    }
    for(int i = m; i >= 1; i--){
        int x = i;
        while(x % 2 == 0){
            cnt2--;
            x /= 2;
        }
    }
    ll a = work5(n), b = work5(m), c = work5(n - m);
    cout << min(a - b - c, cnt2) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}