#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void solve() {
    string s;
    cin >> s;
    vector<int> cnt(26);
    for(char c : s) {
        cnt[c - 'a']++;
    }    
    int mx = ranges::max(cnt);
    int sum = s.size();
    int mxidx;
    for(int i = 0; i < 26; i++) {
        if(cnt[i] == mx) {
            mxidx = i;
            break;
        }
    }
    auto get = [&](int n) -> string {
        vector<int> val(n + 1);
        int p = 0;
        for(int j = 0; j < cnt[mxidx] && j < (n + 1) / 2; j++) {
            val[++p] = mxidx;
        }
        for(int i = 0; i < 26; i++) {
            if(i == mxidx) continue;
            for(int j = 0; j < cnt[i]; j++) {
                val[++p] = i;
            }
        }
        string res;
        for(int i = 1; i <= n / 2; i++) {
            res += 'a' + val[i];
            res += 'a' + val[i + (n + 1) / 2];
        }
        if(n & 1) {
            char c = 'a' + val[(n + 1) / 2];
            if(c == res.back()) {
                res = c + res;
            } else {
                res += c;
            }
        }
        return res; 
    };
    string ans;
    if(mx <= (sum + 1) / 2) {
        ans = get(sum);
    } else {
        int x = sum - mx;
        int rem = mx - (x + 1);
        assert(rem >= 0);

        ans = get(2 * x + 1);
        int ave = rem / (x + 1);
        rem %= (x + 1);
        vector<int> add(x + 1, ave);
        for(int i = 0; i < x + 1; i++) {
            if(rem > 0) {
                add[i]++;
                rem--;
            } else {
                break;
            }
        }
        for(int i = 1; i < x + 1; i++) {
            if(add[i] % 2 == 1) {
                add[i]++;
                if(i + 1 < x + 1 && add[i + 1] % 2 == 1) {
                    add[i + 1]--;
                } else {
                    add[0]--;
                }
            }
        }
        string nans;
        int i = 0;
        for(char c : ans) {
            nans += c;
            if(cnt[c - 'a'] == mx) {
                nans += string(add[i++], c);
            }
        }
        swap(ans, nans);
    }
    cout << ans << "\n";
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
