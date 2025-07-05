#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    ll mx = 0;
    bool ok1 = false, ok2 = false;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        if(a[i] % 2 == 1) ok1 = true;
        if(a[i] % 2 == 0) ok2 = true;
    }
    if(!ok1 || !ok2) {
        cout << mx << "\n";
        return;
    }
    vector<ll> odd, even;
    for(int i = 1; i <= n; i++) {
        if(a[i] % 2 == 0) {
            even.push_back(a[i]);
        } else {
            odd.push_back(a[i]);
        }   
    }
    int esz = even.size(), osz = odd.size();
    ll tot = 0;
    sort(even.begin(), even.end());
    sort(odd.begin(), odd.end(), greater<ll>());
    for(int i = 0; i < esz; i++) {
        tot += odd[i];
        tot += even[i] - 1;
        odd.push_back(1);
    }
    for(int i = esz; i < odd.size(); i++) {
        if(odd[i] != 1) {
            tot += odd[i] - 1;
        } else {
            break;
        }
    }
    tot += 1;
    mx = max(mx, tot);
    cout << mx << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
