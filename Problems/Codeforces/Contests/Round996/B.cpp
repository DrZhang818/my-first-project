#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    int mx = INT_MAX, mn = INT_MAX;
    int c = 0;
    for(int i = 0; i < n; i++){
        if(a[i] < b[i]){
            c++;
            mn = b[i] - a[i];
        }else{
            mx = min(mx, a[i] - b[i]);
        }
    }
    if(c == 0 || c == 1 && mx >= mn){
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