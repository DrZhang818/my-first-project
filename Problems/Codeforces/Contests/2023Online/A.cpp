#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a, b;
    unordered_set<string> st;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        if(!st.contains(s)) {
            a.push_back(s);
            st.insert(s);
        }
    }
    st.clear();
    for(int i = 1; i <= m; i++) {
        string t;
        cin >> t;
        if(!st.contains(t)) {
            b.push_back(t);
            st.insert(t);
        }
    }
    st.clear();
    vector<string> c;
    for(int i = 0, j = 0; i < a.size() || j < b.size(); i++, j++) {
        if(i < a.size()) {
            c.push_back(a[i]);
        }
        if(j < b.size()) {
            c.push_back(b[j]);
        }
    }
    for(int i = 0; i < c.size(); i++) {
        if(!st.contains(c[i])) {
            cout << c[i] << "\n";
            st.insert(c[i]);
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
