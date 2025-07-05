#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n);
    int idx = 0;
    for(int i = 0; i < n; i++) {
        if(a[idx] != 0) {
            cout << -1 << "\n";
            return;
        }
        a[idx] = i + 1;
        idx = (idx + 2) % n;
    }
    for(int i = 0; i < n; i++) {
        cout << a[i] << " \n"[i == n - 1];
    }
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
    
