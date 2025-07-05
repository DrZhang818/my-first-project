#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;



void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    vector<int> ans(n);
    bool ok = true;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> a[j];
        }
        sort(a.begin(), a.end());
        for(int j = 1; j < m; j++){
            if(a[j] != a[j - 1] + n){
                ok = false;
            }
        }
        if(a[0] > n) ok = false;
        if(ok) ans[a[0]] = i + 1;
    }
    if(!ok){
        cout << -1 << "\n";
        return;
    }
    for(auto c : ans){
        cout << c << " ";
    }
    cout << "\n";
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