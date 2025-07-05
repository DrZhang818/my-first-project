#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){ 
    int A, B, C, m;
    cin >> A >> B >> C >> m;
    int n = A * B * C;
    vector<int> x1(m + 1), y1(m + 1), z1(m + 1), x2(m + 1), y2(m + 1), z2(m + 1), hp(n + 1), h(m + 1);
    auto num = [&](int a, int b, int c) -> int {
        if(a == 0 || b == 0 || c == 0 || a > A || b > B || c > C) return 0;
        return ((a - 1) * B + (b - 1)) * C + (c - 1) + 1;
    };
    for(int i = 1; i <= n; i++) {
        cin >> hp[i];
    }
    for(int i = 1; i <= m; i++) {
        cin >> x1[i] >> x2[i] >> y1[i] >> y2[i] >> z1[i] >> z2[i] >> h[i];
    }
    vector<int> D(n + 1);
    auto check = [&](int x) -> bool {
        D.assign(n + 1, 0);
        for(int i = 1; i <= x; i++) {
            D[num(x1[i], y1[i], z1[i])] += h[i];
            D[num(x1[i], y1[i], z2[i] + 1)] -= h[i];
            D[num(x1[i], y2[i] + 1, z1[i])] -= h[i];
            D[num(x1[i], y2[i] + 1, z2[i] + 1)] += h[i];
            D[num(x2[i] + 1, y1[i], z1[i])] -= h[i];
            D[num(x2[i] + 1, y1[i], z2[i] + 1)] += h[i];
            D[num(x2[i] + 1, y2[i] + 1, z1[i])] += h[i];
            D[num(x2[i] + 1, y2[i] + 1, z2[i] + 1)] -= h[i];
        }
        D[0] = 0;
        for(int i = 1; i <= A; i++) {
            for(int j = 1; j <= B; j++) {
                for(int k = 1; k <= C; k++) {
                    D[num(i, j, k)] += D[num(i - 1, j, k)];
                }
            }
        }
        for(int i = 1; i <= A; i++) {
            for(int j = 1; j <= B; j++) {
                for(int k = 1; k <= C; k++) {
                    D[num(i, j, k)] += D[num(i, j - 1, k)];
                }
            }
        }
        for(int i = 1; i <= A; i++) {
            for(int j = 1; j <= B; j++) {
                for(int k = 1; k <= C; k++) {
                    D[num(i, j, k)] += D[num(i, j, k - 1)];
                    if(D[num(i, j, k)] > hp[num(i, j, k)]) {
                        return true;
                    }
                }
            }
        }
        return false;
    };
    int l = 0, r = m + 1;
    while(l + 1 < r) {
        int mid = l + (r - l) / 2;
        if(check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << r << "\n";
} 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}

