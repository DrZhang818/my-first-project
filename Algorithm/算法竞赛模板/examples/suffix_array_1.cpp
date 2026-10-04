#include "../code/suffix_array.hpp"
int main() {
    SA s("banana");
    int a = s.rk[2], b = s.rk[4];
    if(a > b) {
        swap(a, b);
    }
    int ans = INT_MAX;
    for(int i = a + 1; i <= b; i++) {
        ans = min(ans, s.height[i]);
    }
    assert(ans == 3); // anana 与 ana；多询问用ST预处理height。
}
