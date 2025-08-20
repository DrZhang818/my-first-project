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
    if(s == "red") {
        cout << "SSS\n";
    } else if(s == "blue") {
        cout << "FFF\n";
    } else if(s == "green") {
        cout << "MMM\n";
    } else {
        cout << "Unknown\n";
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
