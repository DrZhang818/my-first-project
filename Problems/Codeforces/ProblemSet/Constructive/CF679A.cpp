#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

const int N = 50;
vector<int> primes;
vector<int> spf;
void sieve() {
    spf.resize(N + 1);
    for(int i = 2; i <= N; i++) {
        if(!spf[i]) {
            primes.push_back(i);
            for(int j = 1; i * j <= N; j++) {
                spf[i * j] = i;
            }
        }
    }
}
void solve() {
    int cnt = 0;
    for(int i = 0; i < primes.size(); i++) {
        cout << primes[i] << endl;
        string s;
        cin >> s;
        if(s == "yes") {
            if(primes[i] <= 10) {
                cout << primes[i] * primes[i] << endl;
                cin >> s;
                if(s == "yes") {
                    cnt++;
                }
            }
            cnt++;
        }
        if(cnt >= 2) break;
    }
    if(cnt >= 2) {
        cout << "composite" << endl;
    } else {
        cout << "prime" << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve();
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
