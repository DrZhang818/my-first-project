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
    string s;
    cin >> s;
    string t = s;
    sort(t.begin(), t.end());
    if(s == t) {
        cout << "Bob\n";
        return;
    }
    cout << "Alice\n";
    int i = 0;
    while(s[i] == '0') i++;
    int j = i;
    while(s[j] == '1') j++;
    j--;
    int c1 = j - i + 1;
    int c0 = 0;
    for(int p = j + 1; p < n; p++) {
        c0 += s[p] == '0';
    }
    vector<int> ans;
    if(c1 >= c0) {
        for(int p = i; p <= j; p++) {
            ans.push_back(p + 1);
        }
        for(int p = j + 1; p < n; p++) {
            if(s[p] == '0') {
                ans.push_back(p + 1);
            }
        }
    } else {
        while(j < n && c1 < c0) {
            j++;
            if(s[j] == '1') {
                c1++;
            } else {
                c0--;
            }
        }

        for(int p = i; p <= j; p++) {
            if(s[p] == '1') {
                ans.push_back(p + 1);
            }
        }
        for(int p = j; p < n; p++) {
            if(s[p] == '0') {
                ans.push_back(p + 1);
            }
        }
    }
    cout << ans.size() << "\n";
    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
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
