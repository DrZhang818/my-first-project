#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    for(int t = 1; t <= 20; t++) {
        cerr << "t: " << t << "\n";
        for(int x = t; x <= 100; x++) {
            if(x % t == 0) continue;
            if(t + x % t > (x - t) / 2) {
                cerr << x << " ";                
            }
        }
        cerr << '\n';
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
    