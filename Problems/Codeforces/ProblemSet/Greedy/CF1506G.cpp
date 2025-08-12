#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    vector<char> a;
    vector<int> cnt(26);
    vector<int> vis(26);
    for(char c : s) {
        cnt[c - 'a']++;
    }
    for(char c : s) {
        cnt[c - 'a']--;
        if(vis[c - 'a']) continue;
        while(!a.empty() && c > a.back() && cnt[a.back() - 'a']) {
            vis[a.back() - 'a'] = false;
            a.pop_back();
        }
        a.push_back(c);
        vis[c - 'a'] = true;
    }
    for(char c : a) {
        cout << c;
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
