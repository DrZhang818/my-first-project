#include "../code/li_chao.hpp"
int main() {
    LiChao s(-1000000, 1000000);
    s.addLine(3, 5);
    s.addLine(-2, 1);
    assert(s.query(7) == -13);
}
