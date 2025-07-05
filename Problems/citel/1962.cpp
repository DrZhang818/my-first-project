#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;


void solve(){
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> nums(n - 1);
    for(int i = 0; i < n - 1; i++){
        cin >> nums[i];
        ans += (ll)(i + 2) * nums[i];
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