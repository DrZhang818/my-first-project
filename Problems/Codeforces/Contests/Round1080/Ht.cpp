#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int get(int L, int R) {
    return rng() % (R - L + 1) + L;
}

void solve() {  
    while(1) {
        vector<array<pair<int,int>,3>> points;
        vector<vector<int>> vis(82, vector<int>(82));

        auto gen = [&]() {
            
            for(int i = 0; i < 3; i++) {
                
            }
        };
    }    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
