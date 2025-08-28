void add(int &x, int y) {
    x += y - MOD; x += x >> 31 & MOD;
}
int mod(ll x) {
    return (x % MOD + MOD) % MOD;
}

using Matrix = array<array<int,2>,2>;
using Vector = array<int,2>;

Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                add(c[i][j], 1LL * a[i][k] * b[k][j] % MOD);
            }
        }
    }
    return c;
}

Vector operator * (const Matrix &a, const Vector &b) {
    Vector c{};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            add(c[i], 1LL * a[i][j] * b[j] % MOD);
        }
    }
    return c;
}

Matrix mat{1, 1, 1, 0};

Matrix fast_pow(Matrix a, ll b) {
    Matrix res{1, 0, 0, 1};
    while(b) {
        if(b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
