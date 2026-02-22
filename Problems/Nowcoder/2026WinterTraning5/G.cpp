#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    vector<vector<int>> to(4, vector<int>(6));

    to[0] = {3, 0, 1, 2, 1, 3};
    to[1] = {2, 3, 0, 1, 2, 0};
    to[2] = {1, 2, 3, 0, 3, 1};
    to[3] = {0, 1, 2, 3, 0, 2};

    string s = "0112233445142015320125410214530214510214102302142025101203201451451522302514203214510021454101002532";

    int n = s.size();
    cout << n << "\n";

    int cur = 0;
    for(int i = 0; i < n; i++) {
        cur = to[cur][s[i] - '0'];
        cout << cur;
    }    

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
