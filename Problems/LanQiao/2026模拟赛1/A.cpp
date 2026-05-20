#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using db = double;
constexpr int inf = 1E9;

constexpr int a[] = {13, 1, 2, 3, 5, 4, 4, 2, 2, 2};

constexpr int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
    i64 ans = 0;
    for(int Y = 2000; Y <= 2024; Y++) {
        int limM = Y == 2024 ? 4 : 12;
        
        int x = 0;
        for(int i = 0, t = Y; i < 4; i++) {
            x += a[t % 10];
            t /= 10;
        }

        for(int M = 1; M <= limM; M++) {
            int limD = (Y == 2024 && M == limM) ? 13 : days[M - 1];
            
            int y = 0;
            for(int i = 0, t = M; i < 2; i++) {
                y += a[t % 10];
                t /= 10;
            }

            if((Y % 4 == 0 && Y % 100 != 0 || Y % 400 == 0) && M == 2) {
                limD++;
            }
            for(int D = 1; D <= limD; D++) {
                int tot = x + y;

                for(int i = 0, t = D; i < 2; i++) {
                    tot += a[t % 10];
                    t /= 10;
                }

                if(tot > 50) {
                    ans++;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}