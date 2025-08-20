#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    vector<int> a(6);
    for(int i = 1; i <= 5; i++) {
        cin >> a[i];
    }
    int k;
    cin >> k;
    if(a[5] - a[1] > k) {
        cout << ":(\n";
    } else {
        cout << "Yay!\n";
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
