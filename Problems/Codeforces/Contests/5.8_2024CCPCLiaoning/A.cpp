#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    unordered_set<string> st;
    string s;
    getline(cin, s);
    string t;
    int n, ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> t;
        st.insert(t);
    }
    istringstream ss(s);
    while(ss >> t) {
        if(!isalpha(t.back())) t.pop_back();
        for(int i = 0; i < t.size(); i++) {
            t[i] = tolower(t[i]);
        }
        if(!st.count(t)) {
            st.insert(t);
            ans++;
        }
    }
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
