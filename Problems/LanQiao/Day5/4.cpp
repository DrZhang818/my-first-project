#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> diff(n + 1), cnt(n);
    while(q--){
        int l, r;
        cin >> l >> r;
        diff[--l] += 1;
        diff[r] -= 1;
    }
    int cur = 0;
    for(int i = 0; i < n; i++){
        cur += diff[i];
        cnt[i] = cur;
    }
    sort(a.begin(), a.end(), greater<int>());
    sort(cnt.begin(), cnt.end());
    ll ans = 0;
    for(int i = 0; i < n; i++){
        ans += a[i] * cnt[i];
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