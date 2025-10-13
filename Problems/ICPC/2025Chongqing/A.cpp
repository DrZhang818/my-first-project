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
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto ck = [&]() {
        for(int i = 0; i < n; i++) {
            if(i && a[i] != a[i - 1]) {
                return false;
            }
        }
        return true;
    };
    for(int i = 0; ; i++) {
        if(ck()) {
            cout << i << "\n";
            return;
        }
        auto b = a;
        for(int j = 0; j < n; j++) {
            int nj = i + 1 + j;
            b[j] |= a[(i + 1 + j) % n];
        }
        swap(a, b);
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
