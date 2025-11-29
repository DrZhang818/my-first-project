#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> pos;
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            pos.push_back(i + 1);
        }
    }
    cout << pos.size() << "\n";
    for(int i = 0; i < pos.size(); i++) {
        cout << pos[i] << " \n"[i == pos.size() - 1];
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
