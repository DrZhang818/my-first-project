#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://codeforces.com/problemset/problem/2014/D
void solve() {
    int n, d, k;
    cin >> n >> d >> k;
    vector<int> a(n + d + 1);
    for(int i = 1; i <= k; i++) {
        int l, r;
        cin >> l >> r;
        a[l]++;
        a[r + d]--;
    }
    for(int i = 1; i <= n + d; i++) {
        a[i] += a[i - 1];
    }
    int mnidx = d, mxidx = d;
    for(int i = d + 1; i <= n; i++) {
        if(a[i] < a[mnidx]) {
            mnidx = i;
        }
        if(a[i] > a[mxidx]) {
            mxidx = i;
        }
    }
    mnidx = mnidx - d + 1;
    mxidx = mxidx - d + 1;
    cout << mxidx << " " << mnidx << "\n";
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
