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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    int x = 0, y = 0, pos = 0, neg = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i] == 1 && b[i] == 1) {
            pos++;
        } else if(a[i] == -1 && b[i] == -1) {
            neg++;
        } else if(a[i] == 1) {
            x += 1;
        } else if(b[i] == 1) {
            y += 1;
        }
    }
    if(x > y) {
        swap(x, y);
    }
    if(pos) {
        int t = min(pos, y - x);
        x += t;
        pos -= t;
        x += pos / 2;
        y += (pos + 1) / 2;
    }
    if(neg) {
        int t = min(neg, y - x);
        y -= t;
        neg -= t;
        x -= (neg + 1) / 2;
        y -= neg / 2;
    }
    cout << x << "\n";
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
