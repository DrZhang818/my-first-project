#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int N = log2(n);
    vector<vector<int>> st(n + 1, vector<int>(N + 1));
    for(int i = 1; i <= n; i++) {
        st[i][0] = a[i];
    }
    for(int s = 1; s <= N; s++) {
        for(int i = 1; i + (1 << s - 1) <= n; i++) {
            st[i][s] = min(st[i][s - 1], st[i + (1 << s - 1)][s - 1]);
        }
    }
    int M = log2(m);
    for(int i = 1; i <= n - m + 1; i++) {
        cout << min(st[i][M], st[i + m - (1 << M)][M]) << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

