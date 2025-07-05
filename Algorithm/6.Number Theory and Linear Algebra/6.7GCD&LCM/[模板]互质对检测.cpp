#include<bits/stdc++.h>
using namespace std;
typedef long long LL; 
const int M = 1e6 + 5;

LL minp[M], cnt[M];

void getMinP() {
    for (int i = 1; i <= M - 5; ++i) {
        minp[i] = i;
    }
    for (int i = 2; i <= M - 5; ++i) {
        if (minp[i] == i) {
            for (int j = i + i; j <= M - 5; j += i) {
                if (minp[j] == j) minp[j] = i;
            }
        }
    }
}

LL ans = 0, n;

void main2() {
    getMinP();
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        vector<int> v;
        while (x > 1) {
            int y = minp[x];
            v.push_back(y);
            while (x % y == 0) {
                x /= y;
            } 
        }
        for (int j = 1; j < (1 << (int)v.size()); ++j) {
            LL tmp = 1, one = 0; 
            for (int k = 0; k < (int)v.size(); ++k) {
                if ((j & (1 << k)) > 0) {
                    ++one;
                    tmp *= v[k];
                }
            }
            ans += ((LL)(one % 2 == 0) ? -1 : 1) * cnt[tmp];
            ++cnt[tmp];
        }
    }
    cout << n * (n - 1) / 2 - ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    LL _ = 1;
//  cin >> _;
    while (_--) main2();
    return 0;
}
