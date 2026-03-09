#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve(int n, int k) {  
    if((n - 1) % (k + 1) == 0) {
        cout << "Jiang\n";
    } else {
        cout << "Tang\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k;
    while(cin >> n >> k) {
        if(n == 0 && k == 0) {
            break;
        }
        solve(n, k);
    }
    return 0;
}
