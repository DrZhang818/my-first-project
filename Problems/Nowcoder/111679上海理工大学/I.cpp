#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const ll inf = 1e18;


void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> l(m, -1), r(m, -1);
    for(int i = 0; i < n; i++) {
        if(s[i] == '?') continue;
        int x = s[i] - 'a';
        if(l[x] == -1) l[x] = i;
        r[x] = i;
    }
    vector<int> t;
    for(int i = 0; i < m; i++) {
        if(l[i] == -1) {
            t.push_back(i);
            continue;
        }
        int L = l[i], R = r[i];
        for(int j = L; j <= R; j++) {
            if(s[j] == '?') {
                s[j] = 'a' + i;
            }
        }       
    }
    char las = '#';
    for(int i = 0; i < n; i++) {
        if(s[i] != '?') {
            las = s[i];
        } else if(!t.empty()) { 
            las = 'a' + t.back();
            t.pop_back();
            s[i] = las;
            l[las - 'a'] = i;
            r[las - 'a'] = i;
        } else if(las != '#') {
            s[i] = las;
            r[las - 'a'] = max(r[las - 'a'], i);
        }
    }
    las = '#';
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] != '?') {
            las = s[i];            
        } else {
            s[i] = las;
            l[las - 'a'] = min(l[las - 'a'], i);
        }
    }
    int ans = 0;
    for(int i = 0; i < m; i++) {
        ans += r[i] - l[i];
    }
    cout << ans << "\n";
    cout << s << "\n";
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
