#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
using i128 = __int128;
constexpr int N = 1E5;

ostream& operator<<(ostream& os, i128 n) {
    if(n == 0) return os << 0;
    string s;
    while(n > 0) {
        s += (char)('0' + (n % 10));
        n /= 10;
    }
    for(int i = 0; i < s.size() / 2; i++) {
        swap(s[i], s[s.size() - 1 - i]);
    }
    return os << s;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<i64> cnt(N + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
    }

    vector<i64> in(N + 1);
    vector<i64> out(N + 1);

    for(int d = 1; d <= N; d++) {
        if(!cnt[d]) continue;
        for(int x = d; x <= N; x += d) {
            in[x] += cnt[d];
            out[d] += cnt[x];
        }
    }

    i128 E = 0;
    i128 sum = 0;
    i128 C2 = 0;

    for(int x = 1; x <= N; x++) {
        C2 += cnt[x] * (cnt[x] - 1);
    }

    for(int i = 1; i <= n; i++) {
        int x = a[i];
        E += out[x] - 1;
        sum += (i128)(in[x] + out[x] - 2) * (in[x] + out[x] - 2); 
    }

    i128 ans = E * E - sum + E + C2;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}