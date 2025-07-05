#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &c : a) cin >> c;
    bool ok = true;
    for(int i = 0; i < n - 1; i++){
        if(a[i + 1] < a[i]){
            ok = false;
            break;
        }
        int mn = min(a[i], a[i + 1]);
        a[i] -= mn;
        a[i + 1] -= mn;
    } 
    if(ok){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
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