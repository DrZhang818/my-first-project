#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;
const int N = 100000;
const int M = 25000;
const int B = 103;
const int C = 11789;


int query(vector<int> &a) {
    cout << "? " << a.size();
    for(int x : a) { 
        cout << " " << x;
    }
    cout << endl;
    int res;
    cin >> res;
    return res;
}

void answer(int x) {
    cout << "! " << x << endl;
}


void solve() {
    vector<int> a(C, B);
    int x = query(a);
    if(x == 0) {
        a = vector<int>(B * B, 1);
        x = query(a);
        answer((B * B + x - 1) / x);
        return;
    }
    vector<int> val;
    for(int w = B; w <= N; w++) {
        if((C + (w / B) - 1) / (w / B) == x) {
            val.push_back(w);
        }
    }
    a.clear();
    for(int i = 0; i < val.size(); i++) {
        a.push_back(val[0]);
        a.push_back(i + 1);
    }
    x = query(a);
    answer(val[0] + 2 * val.size() - x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}


// PII get() {
//     for(int B = 100; B <= N; B++) {
//         if(B * B > M) break;
//         for(int C = 1; C <= N; C++) {
//             if(B * B + C > M) break;

//             int mxlen = 0;

//             for(int w = B, pre = -1, len = -1; w <= N; w++) {
//                 int x = (C + (w / B) - 1) / (w / B);
//                 if(x != pre) {
//                     pre = x;
//                     len = 1;
//                 } else {
//                     len++;
//                 }
//                 mxlen = max(mxlen, len);
//             }

//             if(2LL * mxlen + C <= M) {
//                 return make_pair(B, C);
//             }
//         }
//     }
// }