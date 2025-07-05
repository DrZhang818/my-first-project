#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;


    
void solve() { 
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    vector<int> b(n);
    int idx = 0;
    for(int i = 1; i < n; i += 2) {
        b[i] = a[idx++];
    }
    for(int i = 0; i < n; i += 2) {
        b[i] = a[idx++];
    }
    int cnt = 0;
    for(int i = 1; i < n; i += 2) {
        if(i + 1 < n && b[i] < b[i - 1] && b[i] < b[i + 1]) {
            cnt += 1;
        }
    }
    cout << cnt << "\n";
    for(int i = 0; i < n; i++) {
        cout << b[i] << " \n"[i == n - 1];  
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}
    
