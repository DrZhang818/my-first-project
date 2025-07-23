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
    vector<int> a;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '#') {
            a.push_back(i + 1);
        }
    }
    for(int i = 0; i < a.size(); i += 2) {
        cout << a[i] << "," << a[i + 1] << "\n";
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
