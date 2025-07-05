#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    int cur = 0;
    int temp = n;
    while(temp > 9){
        temp /= 10;
        cur++;
    }
    ll ans = 0;
    ans += (n - pow(10, cur) + 1) * (cur + 1);
    
    while(cur > 0){
        ans += cur * (pow(10, cur) - pow(10, cur - 1));
        cur--;
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