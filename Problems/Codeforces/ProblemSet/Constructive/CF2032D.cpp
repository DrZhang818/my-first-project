#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using db = double;
using u64 = unsigned long long;
constexpr int inf = 1000000000;

int query(int u, int v) {
    cout << "? " << u << " " << v << endl;
    int res;
    cin >> res;
    return res;
}

void solve() {  
    int n;
    cin >> n;

    vector<int> vec;

    int end = 1;
    vector<int> p(n);

    int X = -1;

    for(int i = 2; i < n; i++) {
        auto res = query(1, i);
        if(res == 1) {
            vec.push_back(i);
        } else {
            p[i] = end;
            end = i;
            if(X == -1) {
                X = i;
            }
        }
    }

    queue<int> q;
    for(int u : vec) {
        if(u < X) {
            q.push(u);
            continue;
        }

        while(q.size() > 1 && query(u, q.front()) == 1) {
            q.pop();
        }

        p[u] = q.front();
        q.pop();
        q.push(u);
    }

    cout << "!";
    for(int i = 1; i < n; i++) {
        cout << " " << p[i];
    }
    cout << endl;
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
