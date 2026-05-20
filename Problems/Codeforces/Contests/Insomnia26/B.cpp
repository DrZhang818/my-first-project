#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1E9;

bool is_prime[20];

void solve() {
    int n;
    cin >> n;
    if(n < 5) {
        if(n == 1) {
            cout << 1 << "\n";
        } else if(n == 4) {
            cout << 2 << " " << 4 << " " << 1 << " " << 3 << "\n";
        } else {
            cout << -1 << "\n";
        }
        return;
    }

    vector<int> vis(n + 1);
    vector<int> ans {1, 3, 5};
    vis[1] = vis[3] = vis[5] = 1;
    for(int i = 10; i <= n; i += 5) {
        for(int j = i - 8; j <= i; j += 2) {
            ans.push_back(j);
            vis[j] = 1;
        }
    }
    vector<int> p;
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) {
            p.push_back(i);
        }
    }

    do {
        bool ok = true;
        for(int i = 1; i < p.size(); i++) {
            if(!is_prime[abs(p[i] - p[i - 1])]) {
                ok = false;
                break;
            }
        }        
        if(ok) {
            ans.insert(ans.end(), p.begin(), p.end());
            break;
        }
    } while (next_permutation(p.begin(), p.end()));

    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    for(int x : {2, 3, 5, 7, 11, 13, 17, 19}) {
        is_prime[x] = true;
    }

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
