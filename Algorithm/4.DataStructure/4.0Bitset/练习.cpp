#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef unsigned long long ull;
const int inf = 1000000000;

/*
    习题1:
    题目描述: 给你两个包含 1 到 N 之间整数的集合 A 和 B。
    请使用 bitset 分别表示这两个集合，
    并输出它们的并集、交集和 A 相对于 B 的差集中的所有元素。
*/
// const int N = 1005;
// bitset<N> A, B;
// void solve1() {
//     int n;
//     cin >> n;
//     for(int i = 1; i <= n; i++) {
//         int x;
//         cin >> x;
//         A.set(x);
//     }
//     for(int i = 1; i <= n; i++) {
//         int x;
//         cin >> x;
//         B.set(x);
//     }
//     bitset<N> C = A & (~B);
//     for(int i = C._Find_first(); i < N; i = C._Find_next(i)) {
//         cout << i << " ";
//     }
//     cout << "\n";
// }

/*
    习题2:
    题目描述: 给你一个整数 N (1 <= N <= 100000)。再给你 M 个整数。
    请输出所有从 1 到 N 中，没有出现在给定的 M 个整数中的数字。
*/
const int N = 100005;
bitset<N> A;
void solve2() {
    int n; cin >> n;
    A.set();
    for(int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        A.reset(x);
    }
    for(int i = A._Find_first(); i < N; i = A._Find_next(i)) {
        cout << i << " ";
    }
    cout << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) {
        solve2();
    }
    return 0;
}
