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
    vector<int> a(n + 1), b(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    vector<int> st;
    st.push_back(0);

    for(int i = 1; i <= n; i++) {
        vector<int> nst;
        for(int x : st) {
            nst.push_back(max(0, x - a[i]));
            nst.push_back(x ^ b[i]);
        }
        sort(nst.begin(), nst.end());
        nst.erase(unique(nst.begin(), nst.end()), nst.end());
        st = move(nst);
    }

    cout << st.back() << "\n";
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
