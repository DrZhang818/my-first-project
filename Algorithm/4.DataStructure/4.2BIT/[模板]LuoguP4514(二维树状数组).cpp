#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() { 
    char c;
    cin >> c;
    int n, m;
    cin >> n >> m;
    vector A(n + 1, vector<int>(m + 1));
    vector B(n + 1, vector<int>(m + 1));
    vector C(n + 1, vector<int>(m + 1));
    vector D(n + 1, vector<int>(m + 1));
    auto add = [&](int x, int y, int d) -> void {
        for(int i = x; i <= n; i += i & -i) {
            for(int j = y; j <= m; j += j & -j) {
                A[i][j] += d;
                B[i][j] += x * d;
                C[i][j] += y * d;
                D[i][j] += x * y * d;
            }
        }
    };
    auto query = [&](int x, int y) -> int {
        int res = 0;
        for(int i = x; i > 0; i -= i & -i) {
            for(int j = y; j > 0; j -= j & -j) {
                res += (x + 1) * (y + 1) * A[i][j];
                res -= (y + 1) * B[i][j];
                res -= (x + 1) * C[i][j];
                res += D[i][j];
            }
        }
        return res;
    };
    while(cin >> c) {
        if(c == 'L') {
            int a, b, c, d, x;
            cin >> a >> b >> c >> d >> x;
            add(a, b, x);
            add(c + 1, d + 1, x);
            add(a, d + 1, -x);
            add(c + 1, b, -x);
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            cout << query(c, d) - query(a - 1, d) - query(c, b - 1) + query(a - 1, b - 1) << "\n";
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
