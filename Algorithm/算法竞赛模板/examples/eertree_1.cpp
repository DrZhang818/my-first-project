#include "../code/eertree.hpp"
int main() {
    PAM s("ababa");
    s.count();
    long long ans = 0;
    for(int u = 2; u < s.size(); u++) {
        ans = max(ans, 1LL * s.tr[u].len * s.tr[u].cnt);
    }
    assert(s.distinct() == 5 && ans == 6);
}
