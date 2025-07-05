#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


void solve() { 
    int n, m;
    cin >> n >> m;
    vector<int> x1(m + 1), y1(m + 1), x2(m + 1), y2(m + 1), d(n * n + 1);
    auto num = [&](int a, int b) -> int {
        if(a == 0 || b == 0 || a > n || b > n) return 0;
        return (a - 1) * n + (b - 1) + 1;
    };
    for(int i = 1; i <= m; i++) {
        cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
    }
    for(int i = 1; i <= m; i++) {
        d[num(x1[i], y1[i])] += 1;
        d[num(x1[i], y2[i] + 1)] -= 1;
        d[num(x2[i] + 1, y1[i])] -= 1;
        d[num(x2[i] + 1, y2[i] + 1)] += 1;
    }
    d[0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            d[num(i, j)] += d[num(i - 1, j)];
        }
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            d[num(i, j)] += d[num(i, j - 1)];
         }
    }
    /*
        递推式写法
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                d[num(i, j)] += d[num(i - 1, j)] + d[num(i, j - 1)] - d[num(i - 1, j - 1)];
            }
        }
    */
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            cout << d[num(i, j)] << " ";
        }
        cout << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

