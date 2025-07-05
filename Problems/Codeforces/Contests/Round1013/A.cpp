#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(10);
    a[0] = 3, a[1] = 1, a[2] = 2, a[3] = 1, a[5] = 1;
    vector<int> b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for(int i = 1; i <= n; i++) {
        a[b[i]]--;
        if(a[0] <= 0 && a[1] <= 0 && a[2] <= 0 && a[3] <= 0 && a[5] <= 0) {
            cout << i << "\n";
            return;
        }
    }
    cout << 0 << "\n";
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
    
