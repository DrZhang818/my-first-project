#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    ll L;
    cin >> n >> L;
    vector<ll> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int pos = -1;
    for(int i = 1; i < n; i++) {
        if(a[i] + a[i + 1] >= L) {
            pos = i;
        }
    }
    if(pos == -1) {
        cout << "Impossible\n";
        return;
    }
    cout << "Possible\n";
    for(int i = 1; i < pos; i++) {
        cout << i << "\n";
    }
    for(int i = n - 1; i >= pos + 1; i--) {
        cout << i << "\n";
    }
    cout << pos << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
