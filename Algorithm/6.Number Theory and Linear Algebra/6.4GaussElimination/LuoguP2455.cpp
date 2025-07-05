#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr db EPS = 1e-7;
void gauss(vector<vector<db>> &a) {
    int n = a.size() - 1;
    for(int cur = 1; cur <= n; cur++) {
        int mx = cur;
        for(int i = 1; i <= n; i++) {
            if(i < cur && abs(a[i][i]) >= EPS) continue;
            if(abs(a[i][cur]) > abs(a[mx][cur])) mx = i;
        }
        swap(a[mx], a[cur]);
        if(abs(a[cur][cur]) < EPS) continue;
        db temp = a[cur][cur];
        for(int j = cur; j <= n + 1; j++) a[cur][j] /= temp;
        for(int i = 1; i <= n; i++) {
            if(i == cur) continue;
            db fac = a[i][cur];
            for(int j = cur; j <= n + 1; j++) a[i][j] -= a[cur][j] * fac;
        }
    }
}
void solve() { 
    int n;
    cin >> n;
    vector<vector<db>> a(n + 1, vector<db>(n + 2));
    for(int i = 1; i <= n; i++) 
        for(int j = 1; j <= n + 1; j++) 
            cin >> a[i][j];
    gauss(a);
    int flag = 1;
    for(int i = 1; i <= n; i++) {
        if(abs(a[i][i]) < EPS && abs(a[i][n + 1]) >= EPS) {
            flag = -1;
            break;
        }
        if(abs(a[i][i]) < EPS) {
            flag = 0;
        }
    }
    if(flag == -1 || flag == 0) {
        cout << flag << "\n";
        return;
    }
    for(int i = 1; i <= n; i++) {
        cout << "x" << i << "=";
        cout << fixed << setprecision(2) << a[i][n + 1] << "\n";
    } 
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
