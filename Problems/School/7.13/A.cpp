#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    bool ok = true;
    if(s[0] != 'A') ok = false;
    int c = 0;
    for(int i = 2; i < s.size() - 1; i++) {
        if(s[i] == 'C') {
            c++;
        }
    }
    if(c != 1) ok = false;
    for(char c : s) {
        if(c != 'A' && c != 'C') {
            if(isupper(c)) {
                ok = false;
            }
        }
    }
    if(ok) {
        cout << "AC\n";
    } else {
        cout << "WA\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
