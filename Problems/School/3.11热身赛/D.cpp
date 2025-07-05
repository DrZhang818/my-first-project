#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n;
    cin >> n;
    vector<db> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for(int i = 1; i < n; i++) {
        db ans = 0;
        int len = 1;
        for(int j = i + 1; j <= n; j++) {
            if((db)(j - i + 1) / (a[j] - a[i]) > ans || (db)(j - i + 1) / (a[j] - a[i]) == ans && a[j] - a[i] < len) {
                ans = (db)(j - i + 1) / (a[j] - a[i]);
                len = a[j] - a[i];
            }
        }
        cout << len << "\n";
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
