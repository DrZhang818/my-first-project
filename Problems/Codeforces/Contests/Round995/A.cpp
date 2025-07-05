#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int> PII;


void solve(){
    int n;
    cin >> n;
    std::vector<int> a(n), b(n);
    for(auto& num : a) cin >> num;
    for(auto& num : b) cin >> num;
    int ans = a[n - 1];
    for(int i = 0; i < n - 1; i++){
        if(a[i] >= b[i + 1]){
            ans += a[i] - b[i + 1];
        }
    }
    cout << ans << "\n";
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
