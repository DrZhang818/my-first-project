#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve(){
    int n, m;
    cin >> n >> m;
    vector<int> next(n + 1);
    iota(next.begin(), next.end(), 1);
    next[n] = 1;
    int cur = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m - 1; j++) {
            cur = next[cur];
        }
        cout << next[cur] << " ";
        next[cur] = next[next[cur]];
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

