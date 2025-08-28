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
    string s;
    cin >> s;
    int x = 0;
    for(int i = 0; i <= n; i++) {
        if(s[i] == 'A') {
            x++;
        } else {
            x--;
        }
        if(i >= 1) {
            if(x >= 0) {
                cout << "Alice\n";
            } else {
                cout << "Bob\n";
            }
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
