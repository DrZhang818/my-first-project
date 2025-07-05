#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


struct info {
    int st, en;
    friend bool operator < (const info &a, const info &b) {
        return a.en < b.en;
    }
};
void solve() { 
    int n;
    scanf("%d", &n);
    vector<info> a(n + 1);
    for(int i = 1; i <= n; i++) {
        int h, m, s;
        scanf("%d:%d:%d", &h, &m, &s);
        int st = s + m * 60 + h * 3600;
        scanf("%d:%d:%d", &h, &m, &s);
        int en = s + m * 60 + h * 3600;
        a[i] = {st, en};
    }
    sort(a.begin() + 1, a.end());
    int cur = -1, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(a[i].st >= cur) {
            ans++;
            cur = a[i].en;
        }
    }
    cout << ans << "\n";
}

int main()
{

    solve();
    return 0;
}
    
