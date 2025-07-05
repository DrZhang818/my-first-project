#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
string ans;
void dfs(vector<vector<int>> &a, int i, int j) {
    if(i == 7 && j == 1) {
       
        bool ok = true;
        int c0 = 0, c1 = 0, cnt0, cnt1;
        unordered_set<string> st1, st2;
        for(int i = 1; i <= 6; i++) {
            c0 = c1 = cnt0 = cnt1 = 0;
            string s;
            for(int j = 1; j <= 6; j++) {
                if(a[i][j] == 0) c0++, c1 = 0, cnt0++;
                else c1++, c0 = 0, cnt1++;
                if(c0 > 2 || c1 > 2) ok = false;
                s += '0' + a[i][j];
            }
            if(st1.count(s) || cnt0 != cnt1) ok = false;
            st1.insert(s);
        }
        for(int j = 1; j <= 6; j++) {
            c0 = c1 = cnt0 = cnt1 = 0;
            string s;
            for(int i = 1; i <= 6; i++) {
                if(a[i][j] == 0) c0++, c1 = 0, cnt0++;
                else c1++, c0 = 0, cnt1++;
                if(c0 > 2 || c1 > 2) ok = false;
                s += '0' + a[i][j];
            }
            if(st2.count(s) || cnt0 != cnt1) ok = false;
            st2.insert(s);
        }
        if(ok) {
            for(int i = 1; i <= 6; i++) {
                for(int j = 1; j <= 6; j++) {
                    cout << a[i][j] << " \n"[j == 6];
                }
            }
            for(int i = 1; i <= 6; i++) {
                for(int j = 1; j <= 6; j++) {
                    ans += '0' + a[i][j];
                }
            }
        }
        return ;
    }
    if(j < 6) {
        if(a[i][j] == -1) {
            if(j <= 2 || a[i][j - 1] != 0 || a[i][j - 2] != 0) {
                if(i <= 2 || a[i - 1][j] != 0 || a[i - 2][j] != 0) {
                    a[i][j] = 0;
                    dfs(a, i, j + 1);
                }
            }
            if(j <= 2 || a[i][j - 1] != 1 || a[i][j - 2] != 1) {
                if(i <= 2 || a[i - 1][j] != 1 || a[i - 2][j] != 1) {
                    a[i][j] = 1;
                    dfs(a, i, j + 1);
                }
            }
            a[i][j] = -1;
        } else {
            dfs(a, i, j + 1);
        }
    } else {
        if(a[i][j] == -1) {
            if(j <= 2 || a[i][j - 1] != 0 || a[i][j - 2] != 0) {
                if(i <= 2 || a[i - 1][j] != 0 || a[i - 2][j] != 0) {
                    a[i][j] = 0;
                    dfs(a, i + 1, 1);
                }
            }
            if(j <= 2 || a[i][j - 1] != 1 || a[i][j - 2] != 1) {
                if(i <= 2 || a[i - 1][j] != 1 || a[i - 2][j] != 1) {
                    a[i][j] = 1;
                    dfs(a, i + 1, 1);
                }
            }
            a[i][j] = -1;
        } else {
            dfs(a, i + 1, 1);
        }
    }
}
void solve() {
    vector<vector<int>> a(7, vector<int>(7, -1));
    a[1][1] = 1, a[1][2] = 0, a[1][4] = 0, a[2][4] = 0;
    a[3][5] = a[3][6] = a[6][2] = 0;
    a[5][3] = a[5][6] = a[6][5] = 1;
    dfs(a, 1, 1);
    cout << ans << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
