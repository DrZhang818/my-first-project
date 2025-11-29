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
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector<int> idx(n + 1);
    for(int i = 1; i <= n; i++) {
        idx[a[i]] = i;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            int x = a[j], y = x - 1, z = x - 2;
            if(z < 1) continue;
            if(idx[y] < idx[x] || idx[z] < idx[x] || idx[y] < idx[z]) {
                continue;
            }
            int ix = idx[x], iy = idx[y], iz = idx[z];
            a[idx[x]] = z;
            a[idx[y]] = x;
            a[idx[z]] = y;
            idx[z] = ix;
            idx[x] = iy;
            idx[y] = iz;
            j--;
        }
    }
    for(int i = n; i >= 1; i--) {
        for(int j = 1; j <= i; j++) {
            int x = j, y = x - 1, z = x - 2;
            if(z < 1) continue;
            if(idx[y] < idx[x] || idx[z] < idx[x]) {
                continue;
            }
            int ix = idx[x], iy = idx[y], iz = idx[z];
            a[idx[x]] = z;
            a[idx[y]] = x;
            a[idx[z]] = y;
            idx[z] = ix;
            idx[x] = iy;
            idx[y] = iz;
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
    