#include "../code/dujiao_sieve.hpp"
void print(__int128 x) {
    if(x < 0) {
        cout << '-', x = -x;
    }
    if(x >= 10) {
        print(x / 10);
    }
    cout << char('0' + x % 10);
}
int main() {
    DuJiaoSieve s(1000);
    auto [a, b] = s.get(10);
    assert(a == 32 && b == -1);
    print(a);
    cout << ' ' << b << '\n';
}
