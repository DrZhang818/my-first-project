#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

void answer(vector<int> &a) {
    cout << a.size() << " ";
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << " \n"[i == a.size() - 1];
    }
}

void solve() {
    int x, y, z;
    cin >> x >> y >> z;

    vector<int> A, B, C;
    if(x == y) {
        for(int i = 0; i < x; i++) A.push_back(0);
        for(int i = 0; i < z; i++) B.push_back(0), C.psush_back(0);
    } else {
        for(int i = 0; i < x + y; i++) A.push_back(i >= x);
        for(int i = 0; i < z; i++) B.push_back(0);
        for(int i = 0; i < y + z; i++) C.push_back(i < y); 
    }
    answer(A);
    answer(B);
    answer(C);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    while(t--) {
        solve();
    }
    return 0;
}
