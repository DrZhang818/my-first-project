#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int solve(string& s) {  
    int n = s.size();

    auto calc = [&](string& cur) -> int {
        int m = cur.size();
        int res = 0;
        for(int i = 0, j = 0; i < m; i = j) {
            while(j < m && cur[j] == cur[i]) {
                j++;
            }
            res = max(res, j - i);
        }
        return res;
    };

    int ans = inf;

    string t;
    for(int i = 0; i < n; i++) {
        if((s[i] - '0') != (i & 1)) {
            t += s[i];
        }
    }

    ans = min(ans, calc(t));

    t = "";
    for(int i = 0; i < n; i++) {
        if((s[i] - '0') != (~i & 1)) {
            t += s[i];
        }
    }
    ans = min(ans, calc(t));

    return ans;
}

int brute(string& s) {
    int n = s.size();

    auto ck = [&](string& t) {
        for(int i = 1; i < n; i++) {
            if(t[i] == t[i - 1]) {
                return false;
            }
        }
        return true;
    };

    int ans = inf;

    for(int bit = 0; bit < 1 << n; bit++) {
        string t = s;
        for(int i = 0; i < n; i++) {
            if(bit >> i & 1) {
                t[i] ^= 1;
            }
        }
        if(ck(t)) {
            ans = min(ans, int(__builtin_popcount(bit)));
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s = "11000";
    brute(s);
    return 0;


    int n = 5;
    for(int i = 0; i < 1 << n; i++) {
        string s(n, '0');
        for(int j = 0; j < n; j++) {
            if(i >> j & 1) {
                s[j] = '1';
            }
        }

        int ans1 = solve(s);
        int ans2 = brute(s);
        if(ans1 != ans2) {
            cerr << "WA!\n";
            cerr << s << "\n";
            cerr << ans1 << " brute: " << ans2 << "\n";
        }
    }

    // int t = 1;
    // cin >> t;
    // while(t--) {
    //     solve();
    // }
    return 0;
}
