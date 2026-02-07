#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
using namespace __gnu_pbds;

struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template<typename K, typename V>
using umap = gp_hash_table<K, V, CustomHash>;

void solve() {  
    int n;
    cin >> n;

    umap<int,int> mp;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }

    auto val = a;
    sort(val.begin() + 1, val.end());
    val.erase(unique(val.begin() + 1, val.end()), val.end());

    vector<vector<int>> adj(n + 1);
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool> canBe(n + 1, true);

    auto dfs = [&](this auto&& self, int u, int fa) -> umap<int,int> {
        umap<int,int> res;
        for(int v : adj[u]) {
            if(v == fa) continue;
            auto cur = self(v, u);
            if(res.size() < cur.size()) {
                swap(res, cur);
            }
            for(auto [k, v] : cur) {
                res[k] += v;
            }
        }
        auto pos = upper_bound(val.begin() + 1, val.end(), a[u]);
        if(pos == val.end()) {
            canBe[u] = false;
        }
        auto it = res.find(*pos);
        if(it != res.end()) {
            int v = it->first;
            if(res[v] == it->second) {
                canBe[u] = false;
            }
        }
        res[a[u]]++;
        return res;
    };
    
    dfs(1, 0);

    int idx = 0;
    for(int i = 1; i <= n; i++) {
        if(!canBe[i]) {
            continue;
        }
        if(a[i] > a[idx]) {
            idx = i;
        }
    }

    cout << idx << "\n";
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
