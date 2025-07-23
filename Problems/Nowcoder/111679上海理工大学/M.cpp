#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n, M, D;
    cin >> n >> M >> D;
    vector<int> a(M * D + 1);
    for(int i = 1; i <= n; i++) {
        int m1, d1, m2, d2;
        cin >> m1 >> d1 >> m2 >> d2;
        a[(m1 - 1) * D + d1]++;
        a[(m2 - 1) * D + d2 + 1]--;
    }
    for(int i = 1; i <= M * D; i++) {
        a[i] += a[i - 1];
        if(a[i] == 0) {
            int m = (i + D - 1) / D;
            cout << m << " " << i - (m - 1) * D << "\n";
            return;
        }
    }
    cout << "Online\n";
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
