#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using db = double;
constexpr int inf = 1E9;

constexpr int R = 17;
constexpr int M = 100017;

vector<int> w(M), pos(M);

auto init = []() {
    for(int i = 0; i < R; i++) {
        w[i] = 1 << i;
    }
    for(int v = 1, i = R; i < M; v++) {
        if(v & (v - 1)) {
            w[i++] = v;
        }
    }
    for(int i = 0; i < M; i++) {
        pos[w[i]] = i;
    }
    return 1;
}();

void solve1() {
    string s;
    cin >> s;

    int N = s.size() + R;
    string ans(N, '0');

    int _xor = 0;
    for(int i = 0; i < s.size(); i++) {
        ans[R + i] = s[i];
        if(s[i] == '1') {
            _xor ^= w[R + i];
        }
    }

    for(int i = 0; i < R; i++) {
        if(_xor >> i & 1) {
            ans[i] = '1';
        }
    }

    cout << ans << "\n";
}

void solve2() {
    string s;
    cin >> s;

    int _xor = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '1') {
            _xor ^= w[i];
        }
    }

    if(_xor) {
        s[pos[_xor]] ^= 1;
    }

    cout << s.substr(R) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    if(q == 1) {
        solve1(); 
    } else {
        solve2();
    }

    return 0;
}