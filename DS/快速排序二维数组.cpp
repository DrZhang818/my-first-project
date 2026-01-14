#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;
using PII = pair<int,int>;
using ull = unsigned long long;
constexpr int inf = 1000000000;

int p[500], sum[500];
int B[500][500];
// void quickSort(int l, int r) {
//     if(l >= r) return;
//     int x = sum[p[l + r >> 1]];
//     int i = l, j = r;
//     while(i <= j) {
//         while(sum[p[i]] > x) i++;
//         while(sum[p[j]] < x) j--;
//         if(i <= j) {
//             int t = p[i];
//             p[i] = p[j];
//             p[j] = t;
//             i++;
//             j--;
//         }
//     }
//     quickSort(l, j);
//     quickSort(i, r);
// }
void quickSort(int l, int r) {
    if(l >= r) return;
    int x = sum[p[l]];
    int i = l, j = r, t = p[l];
    while(i < j) {
        while(i < j && sum[p[j]] <= x) j--;
        p[i] = p[j];
        while(i < j && sum[p[i]] >= x) i++;
        p[j] = p[i];
    }
    p[i] = t;
    quickSort(l, i - 1);
    quickSort(i + 1, r);
}
void ArraySort(int A[500][500], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            sum[i] += A[i][j];
        }
        p[i] = i;
    }
    quickSort(0, n - 1);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            B[i][j] = A[p[i]][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            A[i][j] = B[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d%c", A[i][j], " \n"[j == n - 1]);
        }
    }
}

int a[500][500] = {{7, 2, 8, 3}, {9, 7, 1, 8}, {4, 3, 6, 5}, {6, 7, 5, 6}};

int main() {

    ArraySort(a, 4);

    return 0;
}
