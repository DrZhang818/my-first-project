#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;



void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    cout << a[n / 2] - a[n / 2 - 1] << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

        solve();
    return 0;
}

