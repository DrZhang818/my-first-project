#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

//https://www.luogu.com.cn/problem/P3265
const db eps = 1E-7;
class Basis {
    vector<vector<db>> b;
public:
    Basis(int m) : b(m) {}
    bool insert(vector<db> &a) {
        for(int i = 0; i < b.size(); i++) {
            if(abs(a[i]) < eps) {
                a[i] = 0;
                continue;
            }
            db x;
            if(b[i].empty()) {
                x = a[i];
                for(int j = i; j < a.size(); j++) {
                    a[j] /= x;
                }
                b[i] = a;
                return true;
            }
            x = a[i];
            for(int j = i; j < a.size(); j++) {
                a[j] -= b[i][j] * x;
                if(abs(a[j]) < eps) a[j] = 0;
            }
        }
        return false;
    }
    
};
void solve() {
    int n, m;
    cin >> n >> m;
    vector a(n + 1, vector<db>(m));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }   
    vector<int> w(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    vector<int> ord(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin() + 1, ord.end(), 
        [&](auto a, auto b){
            return w[a] < w[b];
        });
    Basis b(m);
    int cnt = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(b.insert(a[ord[i]])) {
            cnt++;
            ans += w[ord[i]];
        }
    }
    cout << cnt << " " << ans << "\n";
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
