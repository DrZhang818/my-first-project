#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 500000000;

//https://acm.hdu.edu.cn/showproblem.php?pid=1100
ll C[21];
void init() {
    C[0] = 1;
    for(int i = 1; i <= 20; i++) {
        C[i] = C[i - 1] * (4 * i - 2) / (i + 1);
    }
}
string dfs(int cnt, int ord) {
    if(cnt == 0) return "";
    string res = "";
    for(int i = 0; i <= cnt - 1; i++) {
        ll x = 1LL * C[i] * C[cnt - 1 - i];
        if(x < ord) {
            ord -= x;
        } else {
            int lord = (ord + C[cnt - 1 - i] - 1) / C[cnt - 1 - i];
            int rord = ord % C[cnt - 1 - i];
            if(rord == 0) rord = C[cnt - 1 - i];
            string L = dfs(i, lord);
            string R = dfs(cnt - 1 - i, rord);
            if(i != 0) {
                res += "(";
                res += L;
                res += ")";
            }
            res += "X";
            if(cnt - 1 - i != 0) {
                res += "(";
                res += R;
                res += ")";
            }
            break;
        }
    }
    return res;
}
int n;
void solve() {
    n++;
    int cnt = 0;
    while(C[cnt] < n) n -= C[cnt], cnt++;
    string ans = dfs(cnt, n);
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init();
    while(cin >> n) {
        if(n == 0) break;
        solve();
    }
    return 0;
}
