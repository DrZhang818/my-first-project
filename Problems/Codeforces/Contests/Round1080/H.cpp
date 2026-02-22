#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

void solve() {  
    int n;
    cin >> n;
    if(n == 1) {
        cout << "2\n1 1 1 2 2 1\n2 3 3 2 3 3\n";
        return;
    }

    auto add_2x3 = [&](int x, int y) {
        cout << x << " " << y << " " << x + 1 << " " << y << " " << x << " " << y + 1 << "\n";
        cout << x + 1 << " " << y + 1 << " " << x + 1 << " " << y + 2 << " " << x << " " << y + 2 << "\n";
    };

    auto add_3x2 = [&](int x, int y) {
        cout << x << " " << y << " " << x << " " << y + 1 << " " << x + 1 << " " << y + 1 << "\n";
        cout << x + 1 << " " << y << " " << x + 2 << " " << y << " " << x + 2 << " " << y + 1 << "\n";
    };

    cout << 3 * n * n << "\n";
    if(~n & 1) {
        for(int i = 1; i <= 3 * n; i += 2) {
            for(int j = 1; j <= 3 * n; j += 3) {
                add_2x3(i, j);
            }
        }
        return;
    } 

    cout << "1 1 2 1 3 2\n";
    cout << "2 2 3 3 4 3\n";
    cout << "4 4 5 4 6 5\n";
    cout << "5 5 6 6 7 6\n";
    cout << "3 1 4 1 4 2\n";
    cout << "6 4 7 4 7 5\n";
    cout << "8 4 9 1 9 2\n";
    cout << "8 5 9 3 9 4\n";
    cout << "8 6 9 5 9 6\n";
    cout << "1 2 1 3 2 3\n";
    cout << "4 5 4 6 5 6\n";
    add_2x3(5, 1);
    add_2x3(7, 1);
    add_3x2(1, 4);
    add_3x2(1, 6);
    add_3x2(1, 8);
    add_2x3(4, 7);
    add_2x3(6, 7);
    add_2x3(8, 7);

    for(int i = 10; i <= 3 * n; i += 2) {
        for(int j = 1; j <= 3 * n; j += 3) {
            add_2x3(i, j);
        }
    }

    for(int i = 1; i < 10; i += 3) {
        for(int j = 10; j <= 3 * n; j += 2) {
            add_3x2(i, j);
        }
    }

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
