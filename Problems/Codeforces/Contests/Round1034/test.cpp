#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;


int get(int m) {
    vector<int> fac;
    for(int i = 1; i * i <= m; i++) {
        if(m % i == 0) {
            fac.push_back(i);
            if(i * i != m && i != 1) {
                fac.push_back(m / i);
            }
        }
    }
    return fac.size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int ans = 0;
    for(int i = 2; i <= 500000; i++) {
        ans = max(ans, get(i));
    }
    cout << ans << "\n";
    return 0;
}

