#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int sum = 0;
    vector<int> cnt(64);
    for(int y = 10; y <= 100; y++) {
        cerr << bitset<7>(y) << "\n";
        for(int x = 10; x <= y; x++) {
            if(y % x == (y ^ x)) {
                cout << y << " " << x << "\n";
                cnt[bit_width(unsigned(y))]++;
            }
        }
    }
    for(int i = 0; i < 64; i++) {
        if(cnt[i]) {
            cout << cnt[i] << "\n";
        }
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
