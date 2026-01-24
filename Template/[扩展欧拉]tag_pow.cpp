//递归求解时，模数为 1 就返回 1
//详见LuoguP4139


int tag_pow(ll a, ll b, int MOD) {
    ll res = 1;
    bool tag = false;
    if(a >= MOD) {
        a %= MOD;
        tag = true;
    }
    while(b) {
        if(b & 1) {
            res *= a;
            if(res >= MOD) {
                res %= MOD;
                tag = true;
            }
        }
        a *= a;
        if(a >= MOD) {
            a %= MOD;
            tag = true;
        }
        b >>= 1;
    }
    return res + (tag ? MOD : 0);
}
