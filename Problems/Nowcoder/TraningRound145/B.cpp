#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://ac.nowcoder.com/acm/contest/119666/B

void solve() {
    int n;
    cin >> n;
    vector<string> a;
    for(int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        bool ok = false;
        for(int j = 0; j < s.size() - 1; j++) {
            if(s[j] > s[j + 1]) {
                s.erase(s.begin() + j);
                ok = true;
                break;
            }
        }
        if(!ok) {
            s.pop_back();
        }
        a.emplace_back(s);
    }
    sort(a.begin(), a.end(), 
        [&](auto &x, auto &y) {
            return x + y < y + x;
        });
    string ans;
    for(string &s : a) {
        ans += s;
    }
    cout << ans << "\n";
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
