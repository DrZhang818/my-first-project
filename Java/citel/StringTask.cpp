#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

string S = "aoyeui";

void solve() {  
    string s;
    cin >> s;
    string ans;
    for(char c : s) {
        c = tolower(c);
        if(S.find(c) != string::npos) {
            continue;
        }
        ans += '.' + string(1, c);
    }
    cout << ans << "\n";
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
