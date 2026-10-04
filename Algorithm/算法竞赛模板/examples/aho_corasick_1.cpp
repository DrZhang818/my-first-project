#include "../code/aho_corasick.hpp"
int main() {
    AC s;
    int x = s.add("aba"), y = s.add("ba"), z = s.add("aba");
    s.build();
    auto cnt = s.match("ababa");
    assert(cnt[x] == 2 && cnt[y] == 2 && cnt[z] == 2);
}
