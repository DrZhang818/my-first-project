#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    map<int,int> mp;
    int mx = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        mp[a[i]]++;
        if(mp[a[i]] >= 2){
            mx = max(mx, a[i]);
        }
    }
    if(mx == 0){
        cout << -1 << "\n";
        return;
    }
    vector<int> b(n - 2);
    int idx = 0;
    for(int i = 0; i < n; i++){
        if(a[i] == mx && mp[mx] <= 2){
            continue;
        }
        b[idx++] = a[i];
        if(a[i] == mx) mp[mx]--;
    }
    sort(b.begin(), b.end());
    for(int i = 0; i < n - 3; i++){
        if(abs(b[i] - b[i + 1]) < 2 * mx){
            cout << b[i] << " " << b[i + 1] << " " << mx << " " << mx << "\n";
            return ;
        }
    }
    cout << -1 << "\n";
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