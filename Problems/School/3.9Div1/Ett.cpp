#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1e5 + 5;
int n, a[N];
bool cmp(int a, int b) { return a > b; }
int main(void) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    sort(a + 1, a + 1 + n, cmp);
    for (int i = 1; i <= n; i++) {
        if (a[i + 1] < i + 1) {
            int cnt = 0;
            while(a[i+cnt+1] == i) cnt++;
            const bool f = ((a[i] - i) & 1) || (cnt & 1);
            puts(f ? "First" : "Second");
            break;
        }
    }
    return 0;
}