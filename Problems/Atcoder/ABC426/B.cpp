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
    char x = '#', y = '#';
    int cx = 0, cy = 0;
    for(char c : s) {
        if(c == x) {
            cx++;
        } else if(c == y) {
            cy++;
        } else if(x == '#') {
            x = c;
            cx++;
        } else {
            y = c;
            cy++;
        } 
    }
    if(cx == 1) {
        cout << x << "\n";
    } else {
        cout << y << "\n";
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
