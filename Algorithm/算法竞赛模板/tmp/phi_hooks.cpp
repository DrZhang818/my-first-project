i64 fpe(i64 p, int e) const {
    return powerMod(p % mod, e - 1, mod) * ((p - 1) % mod) % mod;
}
i64 sumFp(i64 x) const {
    int k = get(x);
    return (g1[k] - g0[k] + mod) % mod;
}
i64 sumFpPrefix(int j) const {
    return (sp1[j] - sp0[j] % mod + mod) % mod;
}