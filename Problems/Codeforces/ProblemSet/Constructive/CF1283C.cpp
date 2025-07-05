#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> indeg(n + 1), outdeg(n + 1), cnt(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        if(a[i]) {
            outdeg[i] = 1;
            indeg[a[i]] = 1;
            cnt[i]++;
            cnt[a[i]]++;
        }
    }
    vector<int> in, out;
    for(int i = 1; i <= n; i++) {
        if(!indeg[i]) {
            in.push_back(i);
        }
        if(!outdeg[i]) {
            out.push_back(i);
        }
    }
    sort(in.begin(), in.end(), [&](int a, int b){
        if(cnt[a] != cnt[b]) return cnt[a] < cnt[b];
        return a < b;
    });
    sort(out.begin(), out.end(), [&](int a, int b){
        if(cnt[a] != cnt[b]) return cnt[a] < cnt[b];
        return a < b;
    });
    for(int i = 0; i < out.size(); i++) {
        a[out[i]] = in[(i + 1) % in.size()];
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
