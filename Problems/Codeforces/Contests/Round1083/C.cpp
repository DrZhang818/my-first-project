#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;
constexpr int N = 1000000;

int T[N + 1];
int timer = 0;

void solve() {  
    int n;
    cin >> n;
    
    vector<vector<int>> a(n);

    for(int i = 0; i < n; i++) {
        int m;
        cin >> m;
        timer++;
        a[i].reserve(m);
        vector<int> vec(m);
        for(int j = 0; j < m; j++) {
            int x;
            cin >> x;
            vec[j] = x;
        }      
        for(int j = m - 1; j >= 0; j--) {
            int x = vec[j];
            if(T[x] != timer) {
                T[x] = timer;
                a[i].push_back(x);
            }
        }
    }
    timer++;
    
    vector<bool> used(n);
    vector<int> ans;

    for(int t = 0; t < n; t++) {
        int idx = -1;
        for(int i = 0; i < n; i++) {
            if(used[i]) continue;
            if(idx == -1) {
                idx = i;
            } else {
                for(int j = 0, k = 0; j < a[idx].size() || k < a[i].size(); ) {
                    while(j < a[idx].size() && T[a[idx][j]] == timer) {
                        j++;
                    }
                    while(k < a[i].size() && T[a[i][k]] == timer) {
                        k++;
                    }
                    if(j >= a[idx].size()) {
                        break;
                    } else if(k >= a[i].size()) {
                        idx = i;
                        break;
                    } else if(a[idx][j] < a[i][k]) {
                        break;
                    } else if(a[i][k] < a[idx][j]) {
                        idx = i;
                        break;
                    }
                    j++;
                    k++;
                }
            }
        }
        used[idx] = true;
        for(int x : a[idx]) {
            if(T[x] != timer) {
                T[x] = timer;
                ans.push_back(x);
            }
        }
    }

    for(int x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        timer++;
        solve();
    }
    return 0;
}
