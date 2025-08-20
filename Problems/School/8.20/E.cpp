#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int k;
    cin >> k;
    int h = 21, m = 0;
    h += k / 60;
    m = k % 60;
    cout << h << ":";
    if(m < 10) {
        cout << "0" << m;
    } else {
        cout << m;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
