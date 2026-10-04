#include "../code/sam.hpp"
int main() {
    SAM s;
    for(char c : string("ababa")) {
        s.add(c);
    }
    assert(s.distinct() == 9);
    s.count();
    assert(s.occ("aba") == 2 && s.occ("ba") == 2);
    assert(s.occ("ac") == 0);
    assert(s.lcs("cababd") == 4);
    long long ans = 0;
    for(int u = 1; u < int(s.t.size()); u++) {
        ans += s.t[u].len - s.t[s.t[u].fa].len;
    }
    assert(ans == s.distinct());
}
