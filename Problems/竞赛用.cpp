#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

int get(char a, char b, char c) {
    return (a == 'A') + (b == 'A') + (c == 'A') >= 2;
}

void solve() {
    int n;
    std::cin >> n;
    
    std::string s[2];
    std::cin >> s[0] >> s[1];
    
    std::vector<int> f(n + 1), g(n + 1), h(n + 1);
    for (int i = 0; i < n; i++) {
        if (i % 3 == 0) {
            f[i + 3] = std::max(f[i + 3], f[i] + get(s[0][i], s[0][i + 1], s[0][i + 2]) + get(s[1][i], s[1][i + 1], s[1][i + 2]));
            g[i + 1] = std::max(g[i + 1], f[i] + get(s[0][i], s[0][i + 1], s[1][i]));
            h[i + 1] = std::max(h[i + 1], f[i] + get(s[1][i], s[1][i + 1], s[0][i]));
        }
        if (i % 3 == 1) {
            if (i + 3 < n) {
                g[i + 3] = std::max(g[i + 3], g[i] + get(s[0][i + 1], s[0][i + 2], s[0][i + 3]) + get(s[1][i], s[1][i + 1], s[1][i + 2]));
                h[i + 3] = std::max(h[i + 3], h[i] + get(s[1][i + 1], s[1][i + 2], s[1][i + 3]) + get(s[0][i], s[0][i + 1], s[0][i + 2]));
            }
            f[i + 2] = std::max(f[i + 2], g[i] + get(s[0][i + 1], s[1][i], s[1][i + 1]));
            f[i + 2] = std::max(f[i + 2], h[i] + get(s[1][i + 1], s[0][i], s[0][i + 1]));
        }
    }
    
    std::cout << f[n] << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int t;
    std::cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}
