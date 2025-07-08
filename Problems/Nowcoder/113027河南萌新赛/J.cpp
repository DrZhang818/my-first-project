#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    ll a, b;
    cin >> a >> b;
    vector<ll> c1(1000006), c2(1000006);
    int k = __lg(b);
    c1[k] = a;
    for(int i = k; i >= 1; i--) {
        c1[i - 1] += c1[i] / 2;
        c1[i] %= 2;
    }
    string s;
    cin >> s;
    int st = true, cnt = 2;
    for(char c : s) {
        if(c == 'x') {
            if(st) {
                st = false;
                continue;
            }
            c2[cnt]++;
            cnt = 2;
        } else {
            if(c == '_') {
                cnt++;
            } else {
                cnt--;
                cnt = max(0, cnt);
            }
        }
    }
    c2[cnt]++;
    for(int i = 1000001; i >= 1; i--) {
        c2[i - 1] += c2[i] / 2;
        c2[i] %= 2;
    }
    if(c1 == c2) {
        cout << "LIVE HAPPILY\n";
    } else {
        cout << "ITS MY OWN INVENTION\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
