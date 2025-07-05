#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    ll n;
    cin >> n;
    for(int i = 1; i <= 2; i++) {
        cout << "digit" << endl;
        int x;
        cin >> x;
    }
    int x;
    bool ok = false;
    for(int i = 3; i >= 0; i--) {
        cout << "add " << -(1 << i) << endl;
        cin >> x;
    }
    cout << "add " << n - 1 << endl;
    cin >> x;
    cout << "!" << endl;
    cin >> x;
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
