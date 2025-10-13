#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 998244353;

void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    int sum = 0;
    bool tag = false;
    vector<int> a;
    while(n--) {
        string op;
        cin >> op;
        if(op[1] == 'u') {
            int x;
            cin >> x;
            a.push_back(x);
            add(sum, x);
        } else if(op[1] == 'o') {
            add(sum, MOD - a.back());
            a.pop_back();
        } else {
            sum = 2LL * sum % MOD;
            if(!tag) {
                a.insert(a.end(), a.begin(), a.end());
                if(a.size() >= n) {
                    tag = true;
                }
            }
        }
        cout << sum << "\n";
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
