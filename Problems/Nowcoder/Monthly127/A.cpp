#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;
string s[7] = {"Red", "Orange", "Yellow", "Green", "Blue", "Indigo", "Violet"};
void solve() {  
    vector<int> a(7);
    for(int i = 0; i < 7; i++) {
        cin >> a[i];
    }
    auto i = max_element(a.begin(), a.end()) - a.begin();
    cout << s[i] << "\n";
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
