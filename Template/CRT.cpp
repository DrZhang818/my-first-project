using i128 = __int128;
i64 norm(i64 x, i64 m) {
    x %= m;
    if(x < 0) x += m;
    return x;
}

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i64 x1, y1;
    i64 g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - a / b * y1;
    return g;
}

i64 inv(i64 a, i64 m) {
    i64 x, y;
    exgcd(a, m, x, y);
    return norm(x, m);
}

struct CRT {
    bool ok;
    i128 a;
    i128 m;
};

CRT crt(i64 a, i64 m, i64 b, i64 n) {
    i64 g = gcd(m, n);
    if((b - a) % g) {
        return {false, 0, 0};
    }
    i64 m1 = m / g;
    i64 n1 = n / g;

    i128 mod = (i128)m1 * n;
    i128 t = 0;

    if(n1 != 1) {
        i64 c = norm((b - a) / g, n1);
        i64 iv = inv(m1 % n1, n1);
        t = (i128)c * iv % n1;
    }

    i128 x = (i128)a + (i128)m * t;
    x %= mod;
    if(x < 0) x += mod;

    return {true, x, mod};
}