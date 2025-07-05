#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m), b(k);
    for(auto &num : a) cin >> num;
    for(auto &num : b) cin >> num;
    if(k < n - 1){
        for(int i = 0; i < m; i++){
            cout << 0;
        }
        cout << "\n";
        return;
    }
    if(k == n){
        for(int i = 0; i < m; i++){
            cout << 1;
        }
        cout << "\n";
        return;
    }
    unordered_map<int, int> mp;
    for(auto num : b){
        mp[num]++;
    }
    for(int i = 0; i < m; i++){
        if(mp[a[i]]){
            cout << 0; 
        }else{
            cout << 1;
        }
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
