    #include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;

    
void solve() { 
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    int idx = 1;
    for(int i = 1; i <= k; i += 2) {
        for(int j = i; j <= n; j += k) {
            a[j] = idx++;
        }
    }
    idx = n;
    for(int i = 2; i <= k; i += 2) {
        for(int j = i; j <= n; j += k) {
            a[j] = idx--;
        }
    }
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
    
