#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    vector<int> a;
    int c0 = 0;
    string s;
    cin >> s;
    for(char c : s) {
        int x = c - '0';
        if(x == 0) c0++;
        else a.push_back(x);
    }
    sort(a.begin(), a.end());
    cout << a[0];
    while(c0 > 0) {
        cout << 0;
        c0--;
    }
    for(int i = 1; i < a.size(); i++) {
        cout << a[i];
    }
    cout << "\n";
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
