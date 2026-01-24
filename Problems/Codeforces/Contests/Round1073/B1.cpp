#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    string s;
    cin >> s;
    int i = 0;
    while(s[i] == '(') i++;
    int c = 0;
    for(int j = i + 1; j < n; j++) {
        c += s[j] == '(';
    } 
    if(c >= 2) {
        cout << n - 2 << "\n";
    } else {
        cout << -1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
