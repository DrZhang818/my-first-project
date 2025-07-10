#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    vector<ll> a(n + 1);
    int neg = 0, pos = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        neg += a[i] < 0;
        pos += a[i] > 0;
    }
    if(n <= 2) {
        cout << "Yes\n";
        return;
    }
    sort(a.begin() + 1, a.end(), [&](auto x, auto y){
        return abs(x) < abs(y);
    });
    bool ok = true;
    for(int i = 2; i < n; i++) {
        if(a[i - 1] * a[i + 1] != a[i] * a[i]) {
            ok = false;
            break;   
        }
    }
    if(abs(a[1]) == abs(a[n]) && abs(pos - neg) <= 1) {
        ok = true;
    } 
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
