#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int MOD = 1000000007;
void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    unordered_map<char,int> mp;
    for(char c : s) mp[c]++;
    int k = mp.size();
    int ans = 0;
    for(int i = k; i <= n; i += k) {
        unordered_map<char,int> cnt;
        multiset<int> st;
        for(int j = 0; j < n; j++) {
            st.erase(cnt[s[j]]);
            cnt[s[j]]++;
            st.insert(cnt[s[j]]);
            if(j < i - 1) continue;
            if(cnt.size() == k && *st.begin() == *st.rbegin()) add(ans, 1);
            st.erase(cnt[s[j - i + 1]]);
            cnt[s[j - i + 1]]--;
            if(cnt[s[j - i + 1]] == 0) {
                cnt.erase(s[j - i + 1]);
            } else {
                st.insert(cnt[s[j - i + 1]]);
            }
        }
    }
    cout << ans << "\n";
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
