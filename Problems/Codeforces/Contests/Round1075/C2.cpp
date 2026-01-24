#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;

void solve() {  
    int n;
    cin >> n;
    vector<int> a(n + 1);
    iota(a.begin(), a.end(), 0);
    for(int i = 2; i < n; i += 2) {
        if(i + 1 <= n) {
            swap(a[i], a[i + 1]);
        }
    }
    swap(a[1], a[n]);
    if(n % 2 == 0) {
        int high = 1 << __lg(n);
        if(n ^ high) {
            swap(a[1], a[(n ^ high) + 1]);
        } else {
            cout << "-1\n";
            return;
        }
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
