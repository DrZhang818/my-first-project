#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());

    int L = -1, R = -1;
    for(int i = 3, j = 1; i <= n; i++) {
        while(i - j + 1 > 3 && a[j] + a[j + 1] <= a[i]) {
            j++;
        }
        if(a[j] + a[j + 1] > a[i]) {
            if(L == -1) {
                L = j;
                R = i;
            } else if(i - j + 1 > R - L + 1) {
                L = j;
                R = i;
            }
        }
    }

    if(L == -1) {
        cout << 0 << "\n";
        return;
    }

    cout << R - L + 1 << " ";
    for(int i = L; i <= R; i++) {
        cout << a[i] << " \n"[i == R];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}