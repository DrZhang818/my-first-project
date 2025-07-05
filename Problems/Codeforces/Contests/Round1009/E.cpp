#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;


void solve() { 
    srand(time(0));
    int n;
    cin >> n;
    vector<int> a(3);
    iota(a.begin(), a.end(), 1);
    while(1) { 
        int t, rng;
        cout << "? " << a[0] << " " << a[1] << " " << a[2] << endl;
        cin >> t;
        if(t == 0) break;
        rng = rand() % 3;
        a[rng] = t;
    }
    cout << "! " << a[0] << " " << a[1] << " " << a[2] << endl;
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
    
