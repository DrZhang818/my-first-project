#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

bool ck(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return t == s;
}
void solve() {
    string s;
    cin >> s;
    int n = s.size();
    if(ck(s) && ck(s.substr(0, (n - 1) / 2)) && ck(s.substr((n + 3) / 2 - 1))) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
