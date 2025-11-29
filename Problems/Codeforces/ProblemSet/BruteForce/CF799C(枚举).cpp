#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

struct info {
    int w, c;
    friend bool operator < (const info &a, const info &b) {
        return a.c < b.c;
    }
};

void solve() {
    int N, A, B;
    cin >> N >> A >> B;

    vector<info> a, b;
    for(int i = 1; i <= N; i++) {
        int w, c;
        char tag;
        cin >> w >> c >> tag;
        if(tag == 'C') {
            if(c <= A) {
                a.emplace_back(w, c);
            }
        } else {
            if(c <= B) {
                b.emplace_back(w, c);
            }
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ans = 0, ans2 = 0;
    auto work = [&](vector<info> &a, int S) -> void {
        int n = a.size();
        vector<int> pre(n + 1, -inf);
        for(int i = 0; i < n; i++) {
            pre[i + 1] = max(pre[i], a[i].w);
            auto j = upper_bound(a.begin(), a.begin() + i, info(0, S - a[i].c)) - a.begin() - 1;
            ans = max(ans, a[i].w + pre[j + 1]);
        }
        ans2 += pre[n];
    };
    work(a, A);
    work(b, B);
    ans = max(ans, ans2);
    cout << ans << "\n";
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
