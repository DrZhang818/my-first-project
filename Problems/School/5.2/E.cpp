#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<int> dig(9);
    for(int i = 0; i < n; i++) {
        int num = s[i] - '0';
        if(num == 2) dig[2] += 1;
        if(num == 3) dig[3] += 1;
        if(num == 4) dig[3] += 1, dig[2] += 2;
        if(num == 5) dig[5] += 1;
        if(num == 6) dig[5] += 1, dig[3] += 1;
        if(num == 7) dig[7] += 1;
        if(num == 8) dig[7] += 1, dig[2] += 3;
        if(num == 9) dig[7] += 1, dig[3] += 2, dig[2] += 1;
    }
    for(int i = 9; i >= 2; i--) {
        for(int j = 0; j < dig[i]; j++) {
            cout << i;
        }
    }
    cout << "\n";
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
