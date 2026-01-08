#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int t, m;
    cin >> t >> m;
    string op;
    getline(cin, op);
    int idx = 0;
    vector<int> bel(m + 1);
    for(int i = 1; i <= t; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        string op;
        ss >> op;
        if(op[0] == 'a') {
            vector<int> vec;
            int v;
            while(ss >> v) {
                vec.push_back(v);
            }
            int j = 1, n;
            if(vec.size() == 1) {
                n = vec[0];
            } else {
                j = vec[0];
                n = vec[1];
            }
            int p = -1;
            for(; j <= m - n + 1; j++) {
                bool ok = true;
                for(int k = j; k < j + n; k++) {
                    if(bel[k]) {
                        j = k;
                        ok = false;
                        break;
                    }
                }
                if(ok) {
                    p = j;
                    break;
                }
            }
            if(p == -1) {
                cout << "NULL\n";
                continue;
            }
            fill(bel.begin() + p, bel.begin() + p + n, ++idx);
            cout << idx << "\n";
        } else if(op[0] == 'e') {
            int x;
            ss >> x;
            if(x <= 0 || find(bel.begin() + 1, bel.end(), x) == bel.end()) {
                cout << "ILLEGAL_ERASE_ARGUMENT\n";
                continue;
            }
            replace(bel.begin() + 1, bel.end(), x, 0);
        } else {
            int k = 0;
            vector<int> nbel(m + 1);
            for(int j = 1; j <= m; j++) {
                if(bel[j]) {
                    nbel[++k] = bel[j];
                }
            }
            swap(bel, nbel);
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
