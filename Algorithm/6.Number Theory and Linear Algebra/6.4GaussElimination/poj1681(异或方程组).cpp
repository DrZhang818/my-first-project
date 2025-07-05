#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


constexpr int inf = 1000000000;
int dir[5] = {-1, 0, 1, 0, -1};
void solve() { 
    int n;
    cin >> n;
    int m = n * n;
    vector<vector<int>> A(m, vector<int>(m, 0));
    vector<int> b(m, 0);
    for(int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for(int j = 0; j < n; j++) {
            int idx = i * n + j;
            A[idx][idx] = 1;
            b[idx] = (row[j] == 'w') ? 1 : 0;
            for(int s = 0; s < 4; s++) { 
                int ni = i + dir[s], nj = j + dir[s + 1];
                if(ni >= 0 && ni < n && nj >= 0 && nj < n) {
                    int nidx = ni * n + nj;
                    A[idx][nidx] = 1;
                }
            }
        }
    }
    int rk = 0;
    vector<int> pvtCol;
    vector<int> where(m, -1);
    for(int c = 0; c < m && rk < m; c++) {
        int sel = -1;
        for(int i = rk; i < m; i++) {
            if(A[i][c] == 1) {
                sel = i;
                break;
            }
        }
        if(sel == -1) continue;
        swap(A[sel], A[rk]);
        swap(b[sel], b[rk]);
        where[c] = rk;
        pvtCol.push_back(c);
        for(int i = 0; i < m; i++) {
            if(i != rk && A[i][c] == 1) {
                for(int j = c; j < m; j++) {
                    A[i][j] ^= A[rk][j];
                }
                b[i] ^= b[rk];
            }
        }
        rk++;
    }
    bool ok = true;
    for(int i = rk; i < m; i++) {
        if(b[i] == 1) {
            ok = false;
            break;
        }
    }
    if(!ok) {
        cout << "inf\n";
        return;
    }
    vector<int> freeVars;
    for(int c = 0; c < m; c++) {
        if(where[c] == -1) {
            freeVars.push_back(c);
        }
    }
    int cnt = freeVars.size();
    int best = inf;
    for(int msk = 0; msk < (1 << cnt); msk++) {
        vector<int> x(m, 0);
        for(int i = 0; i < cnt; i++) {
            int var = freeVars[i];
            if(msk & (1 << i)) {
                x[var] = 1;
            } else {
                x[var] = 0;
            }
        }
        for(int c = m - 1; c >= 0; c--) {
            if(where[c] != -1) {
                int i = where[c];
                int sum = 0;
                for(int j = c + 1; j < m; j++) {
                    if(A[i][j] == 1) {
                        sum ^= x[j];
                    }
                }
                x[c] = b[i] ^ sum;
            }
        }
        int cur = 0;
        for(int i = 0; i < m; i++) {
            if(x[i] == 1) {
                cur++;
            }
        }
        best = min(best, cur);
    }
    cout << best << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
