#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 1e6 + 5;

vector<ll> prime;
vector<ll> lpf(N + 1);
void solve() {
    for(int i = 2; i <= N; i++) {
        if(lpf[i] == 0) {
            prime.push_back(i);
            for(int j = 1; j * i <= N; j++) {
                lpf[j * i] = i;
            }
        }
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
    cout << prime[2024] << "\n";
    return 0;
}
