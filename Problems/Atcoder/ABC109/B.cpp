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
    bool ok = true;
    unordered_set<string> st;
    string pre;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if(st.count(s)) {
            ok = false;
        }
        st.insert(s);
        if(i != 1 && s[0] != pre.back()) {
            ok = false;
        }
        pre = s;
    }
    if(ok) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
