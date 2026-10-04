i64 fpe(i64 p, int e) const {
    return e == 1 ? mod - 1 : 0;
}
i64 sumFp(i64 x) const {
    return (mod - g0[get(x)]) % mod;
}
i64 sumFpPrefix(int j) const {
    return (mod - sp0[j] % mod) % mod;
}