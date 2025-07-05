#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    vector<int> a(2 * n);
    for(auto &x : a) cin >> x;
    unordered_map<int, int> cnt;
    int mx = 0;
    for(int i = 0; i < a.size(); i++){
        cnt[a[i]]++;
        mx = max(mx, cnt[a[i]]);
    }
    if(2 * mx <= 3 * n + 1){
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