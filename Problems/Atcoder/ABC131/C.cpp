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
    s = "#" + s;
    for(int i = 1; i <= 4; i++) {
        if(s[i] == s[i - 1]) {
            cout << "Bad\n";
            return;
        }
    }
    cout << "Good\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
