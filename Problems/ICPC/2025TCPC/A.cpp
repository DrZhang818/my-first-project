#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    array<int,3> a;
    for(int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    ranges::sort(a);
    if(a[2] - a[0] >= 10) {
        cout << "check again\n";
    } else {
        cout << "final " << a[1] << "\n";
    }
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
