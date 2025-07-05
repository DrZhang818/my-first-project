#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(int n){ 
    vector<int> a(n + 1);
    for(int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        a[l] += 1;
        a[r + 1] -= 1;
    }
    for(int i = 1; i <= n; i++) {
        a[i] += a[i - 1];
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    while(cin >> n && n != 0) {
        solve(n);
    }    
    return 0;
}

