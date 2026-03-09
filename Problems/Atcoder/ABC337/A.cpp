#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    i64 suma = 0, sumb = 0;
    for(int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        suma += x;
        sumb += y;
    }
    if(suma == sumb) {
        cout << "Draw\n";
    } else if(suma > sumb) {
        cout << "Takahashi\n";
    } else {
        cout << "Aoki\n";
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
