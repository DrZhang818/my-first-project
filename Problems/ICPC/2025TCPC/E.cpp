#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

vector<vector<string>> a(3);

void solve() {
    string s;
    int j, k;
    cin >> s >> j >> k;
    string x = a[s.size() - 2][j - 1];
    string y = a[s.size() - 2][k - 1];
    int c1 = 0, c2 = 0;
    for(int i = 0; i < s.size(); i++) {
        if(x[i] == y[i]) {
            c1++;
        } else {
            c2++;
        }
    }
    cout << c1 << "A" << c2 << "B\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    a[0].push_back("12");
    a[1].push_back("123");
    a[2].push_back("1234");

    for(int i = 0; i < 3; i++) {
        string s = a[i][0];
        while(next_permutation(s.begin(), s.end())) {
            a[i].push_back(s);
        }
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
