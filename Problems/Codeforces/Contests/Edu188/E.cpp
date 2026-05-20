#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;
constexpr int N = 1E6;

vector<int> vec[100];

void solve() {
    string s;
    cin >> s;
    if(s.size() == 1) {
        cout << s << "\n";
        return;
    }

    int sum = 0;
    array<int,10> cnt {};
    for(char c : s) {
        sum += c - '0';
        cnt[c - '0']++;
    }

    auto dfs = [&](this auto&& self, int tar, int sum, const array<int,10>& cnt, string& ans) -> bool {
        if(sum < tar) return false;
        if(sum == tar) {
            for(int i = 9; i >= 0; i--) {
                ans.append(cnt[i], char('0' + i));
            }
            return true;
        }

        if(tar > 54) return false;
        
        for(int i : vec[tar]) {
            if(sum < i) break;

            int x = i;
            bool ok = true;
            auto ncnt = cnt;

            while(x) {
                int pop = x % 10;
                if(--ncnt[pop] < 0) {
                    ok = false;
                    break;
                }
                x /= 10;
            }

            if(ok) {
                if(self(i, sum - tar, ncnt, ans)) {
                    ans += to_string(i);
                    return true;
                }
            }
        }
        return false;
    };

    for(int i = 0; i < 10; i++) {
        if(cnt[i]) {
            cnt[i]--;
            string ans;
            if(dfs(i, sum - i, cnt, ans)) {
                cout << ans << i << "\n";
                return;
            }
            cnt[i]++;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int i = 10; i <= N; i++) {
        int x = i, sum = 0;
        while(x) {
            sum += x % 10;
            x /= 10;
        }
        vec[sum].push_back(i);
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
