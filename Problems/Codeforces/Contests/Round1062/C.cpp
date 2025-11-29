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
    vector<int> a(n + 1);
    bool odd = false, even = false;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i] % 2 == 1) {
            odd = true;
        } else {
            even = true;
        }
    }
    if(odd && even) {
        sort(a.begin() + 1, a.end());
    } 
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
