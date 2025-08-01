#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, s;
    cin >> n >> s;
    vector<int> a(n + 1);
    int sum = 0;
    int c0 = 0, c1 = 0, c2 = 0;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        sum += a[i];
        c0 += a[i] == 0;
        c1 += a[i] == 1;
        c2 += a[i] == 2;        
    }
    if(sum == s) {
        cout << -1 << "\n";
        return;
    }
    if(sum > s) {
        for(int i = 1; i <= n; i++) {
            cout << a[i] << " \n"[i == n];
        }
        return;
    }
    s -= sum;
    if(s > 1) {
        cout << -1 << "\n";
        return;
    }
    for(int i = 0; i < c0; i++) cout << 0 << " ";
    for(int i = 0; i < c2; i++) cout << 2 << " ";
    for(int i = 0; i < c1; i++) cout << 1 << " ";
    cout << "\n";
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
