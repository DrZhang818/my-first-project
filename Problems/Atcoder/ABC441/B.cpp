#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    vector<array<int,26>> vis(2);
    for(char c : s) {
        vis[0][c - 'a'] = 1;
    }
    for(char c : t) {
        vis[1][c - 'a'] = 1;
    }
    auto ck = [&](const string& a, int i) -> bool {
        for(char c : a) {
            if(!vis[i][c - 'a']) {
                return false;
            }
        }
        return true;
    };
    int q;
    cin >> q;
    while(q--) {
        string w;
        cin >> w;
        bool ok0 = ck(w, 0);
        bool ok1 = ck(w, 1);
        if(ok0 && ok1) {
            cout << "Unknown\n";
        } else if(ok0) {
            cout << "Takahashi\n";
        } else {
            cout << "Aoki\n";
        }
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
