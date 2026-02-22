#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

const string t = "AKIHABARA";

void solve() {  
    string s;
    cin >> s;

    if(s.size() > t.size()) {
        cout << "NO\n";
        return;
    }

    int j = 0;
    for(int i = 0; i < s.size(); i++) {
        if(j >= t.size() || s[i] != t[j] && t[j] != 'A') {
            cout << "NO\n";
            return;
        }
        if(s[i] == t[j]) {
            j++;
        } else {
            j++;
            i--;
        }
    }

    if(j < t.size() - 1) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
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
