#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    string s;
    int cnt;
    friend bool operator < (const info &a, const info &b) {
        if(a.cnt != b.cnt) return a.cnt > b.cnt;
        return a.s < b.s;
    }
};
void solve() {
    int n;
    cin >> n;
    unordered_map<string,int> mp;
    for(int i = 1; i <= n; i++) {
        int tag; cin >> tag;
        string s;
        getline(cin, s);
        istringstream ss(s);
        string token;
        while(ss >> token) {
            mp[token]++;
        }
    }
    vector<info> ans;
    for(auto &[s, cnt] : mp) {
        if(cnt >= (n + 1) / 2) {
            ans.push_back({s, cnt});
        }
    }
    sort(ans.begin(), ans.end());
    if(ans.size() == 0) {
        cout << "None\n";
    } else {
        for(int i = 0; i < ans.size(); i++) {
            cout << ans[i].s << "\n";
        }
    }
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
