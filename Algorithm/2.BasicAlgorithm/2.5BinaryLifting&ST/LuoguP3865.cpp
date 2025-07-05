#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    const int N = log2(n);
    vector<vector<int>> ST(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n; i++) {
        ST[i][0] = a[i];
    }
    for(int s = 1; s <= N; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {
            ST[i][s] = max(ST[i][s - 1], ST[i + (1 << s - 1)][s - 1]);
        }
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for(int i = 2; i <= n; i++) {
        lg[i] = lg[i >> 1] + 1;
    }
    while(q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1, s = lg[len], ans;
        ans = max(ST[l][s], ST[r - (1 << s) + 1][s]);
        cout << ans << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

