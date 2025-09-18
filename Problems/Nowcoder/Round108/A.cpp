#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int s, s1, s2, s3;
    cin >> s >> s1 >> s2 >> s3;
    if(s < 425 && min({s1, s2, s3}) < 60) {
        cout << "YES\n"; 
    } else {
        cout << "NO\n";
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
