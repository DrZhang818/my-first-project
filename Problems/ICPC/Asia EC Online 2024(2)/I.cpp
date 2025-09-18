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
    vector<int> a(33, -1);
    a[32] = 1;
    if(n & 1) {
        cout << "YES\n";
        n--;
        for(int i = 31; i >= 1; i--) {
            if(n >> i & 1) {
                a[i] = 1;
            }
        }
    } else {
        if(n % 4 != 2) {
            cout << "NO\n";
            return;
        } 
        cout << "YES\n";
        a[1] = 0;
        n -= 2;
        for(int i = 31; i >= 1; i--) {
            if(n >> i & 1) {
                a[i] = 1;
            }
        }
    }
    for(int i = 1; i <= 32; i++) {
        cout << a[i] << " \n"[i % 8 == 0];
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
