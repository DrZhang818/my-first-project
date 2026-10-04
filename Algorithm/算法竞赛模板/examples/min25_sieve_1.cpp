#include "../code/min25_sieve.hpp"
int main() {
    Min25Sieve s(10, 1000000007);
    assert(s.solve() == 263);
}
