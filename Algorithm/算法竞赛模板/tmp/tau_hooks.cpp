i64 fpe(i64 p, int e) const {
    return (e + 1) % mod;
}
i64 sumFp(i64 x) const {
    return 2 * g0[get(x)] % mod;
}
i64 sumFpPrefix(int j) const {
    return 2 * sp0[j] % mod;
}