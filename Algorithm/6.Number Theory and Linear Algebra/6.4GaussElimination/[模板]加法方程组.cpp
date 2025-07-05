#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr db EPS = 1e-7;
void gauss(vector<vector<db>> &a) {
    int n = a.size();
    for(int cur = 1; cur <= n; cur++) {
        int mx = cur;
        for(int i = 1; i <= n; i++) {
            if(i < cur && abs(a[i][cur]) >= EPS) continue;
            if(abs(a[i][cur]) > a[mx][cur]) mx = i;
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