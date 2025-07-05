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
    string s;
    cin >> s;
    vector<int> cnt(26);
    int ans = 0;
    s = "#" + s;
    for(int i = 1; i <= 2 * n - 2; i++) {
        if(i % 2 == 1) {
            cnt[s[i] - 'a']++;
        } else {
            if(cnt[s[i] - 'A'] == 0) {
                ans++;
            } else {
                cnt[s[i] - 'A']--;
            }
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
