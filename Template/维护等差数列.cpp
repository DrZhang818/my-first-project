vector<ll> d1(n + 5), d2(n + 5);

auto add = [&](int l, int r, ll a1, ll d) {
    d2[l] += a1;
    d2[l + 1] += d - a1;
    d2[r + 1] -= a1 + (r - l + 1) * d;
    d2[r + 2] += a1 + (r - l) * d;
};