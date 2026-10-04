#include "../code/convex_hull_dp.hpp"
int main() {
    CHT s;
    vector<long long> dp(9);
    s.addPoint({0, 0});
    for(int i = 1; i <= 8; i++) {
        dp[i] = (long long)(s.query({-2LL * i, 1}) + 1LL * i * i);
        s.addPoint({i, dp[i] + 1LL * i * i});
    }
    assert(dp[8] == 8);
}
