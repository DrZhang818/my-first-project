#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    string s;
    cin >> n >> s;
    int l = 1, r = n;
    vector<int> p(n + 1);
    for(int i = n; i >= 2; i--) {
        if(s[i - 2] == '<') p[i] = l++;
        else p[i] = r--;
    }
    p[1] = l;
    for(int i = 1; i <= n; i++) {
        cout << p[i] << " \n"[i == n];
    }
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
