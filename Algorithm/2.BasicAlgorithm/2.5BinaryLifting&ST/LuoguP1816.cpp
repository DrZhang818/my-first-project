#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n, m;
    cin >> n >> m;
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
            ST[i][s] = min(ST[i + (1 << s - 1)][s - 1], ST[i][s - 1]);
        }
    }
    while(m--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        len = log2(len);
        cout << min(ST[l][len], ST[r - (1 << len) + 1][len]) << " \n"[m == 0];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
