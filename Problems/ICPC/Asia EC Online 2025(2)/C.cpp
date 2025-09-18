#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

void solve() {
    int S;
    cin >> S;
    vector<int> F(8);
    for(int i = 1; i <= 7; i++) {
        cin >> F[i];
    }

    auto ck = [&](int x) -> bool {
        int c1 = max(0, x - F[1]);
        int c2 = max(0, x - F[2]);
        int c3 = max(0, x - F[4]);
        if(F[3] + F[6] + F[7] < c2 || F[5] + F[6] + F[7] < c3 || F[3] + F[5] + F[6] + F[7] < c2 + c3) {
            return false;
        }
        int rem = F[3] + F[5] + F[7] - max(0, c2 + c3 - F[6]);
        return c1 <= rem;
    };

    int l = -1, r = S + 1;
    while(l + 1 < r) {
        int mid = l + r >> 1;
        if(ck(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
