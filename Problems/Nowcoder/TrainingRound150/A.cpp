#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

void solve() {
    int n;
    cin >> n;
    vector<int> odd(n + 1), even(n + 1);
    int x = 0, y = 0;
    for(int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        if(v & 1) {
            odd[++x] = v;
        } else {
            even[++y] = v;
        }
    }

    sort(odd.begin() + 1, odd.end(), greater());
    sort(even.begin() + 1, even.end(), greater());

    i64 O = odd[1], E = even[1];
    for(int i = 0; i < n; i++) {
        O += even[i];
        E += odd[i];
        if(i > 0 && even[i] == 0) O = 0;
        if(i > 0 && odd[i] == 0) E = 0;
        cout << max(O, E) << " \n"[i == n - 1];
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
