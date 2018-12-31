// https://oi.edu.pl/en/archive/oi/14/osi
// Note: hashing always feels like a bit of a cheese

#include <bits/stdc++.h>

using namespace std;

typedef double T;
const T EPS = (T)(1e-9);

bool eq(T a, T b)
{
    return abs(a - b) <= EPS;
}

typedef uint64_t H;

const H MOD = -1;

H add_mod(H a, H b)
{
    const H c = a + b;
    if (c < a || c < b) {
        return c + 1;
    } else {
        return c;
    }
}

const H lo_mask = (H(1) << 32) - 1;

typedef pair<H, H> phh;

phh long_mul(H a, H b)
{
    H a1 = a & lo_mask, a2 = a >> 32;
    H b1 = b & lo_mask, b2 = b >> 32;
    H sp0 = a1 * b1;
    H sp1 = a1 * b2;
    H sp2 = a2 * b1;
    H sp3 = a2 * b2;
    H lo = sp0 + (sp1 << 32);
    int carry = lo < sp0;
    H lo1 = lo + (sp2 << 32);
    carry += lo1 < lo;
    H hi = sp3 + (sp1 >> 32) + (sp2 >> 32) + carry;
    return make_pair(lo1, hi);
}

H mul_mod(H a, H b)
{
    auto res = long_mul(a, b);
    return add_mod(res.first, res.second);
}

struct K {
    H x;
    K(H x = 0)
        : x(x)
    {
    }
    K operator+(K o) const { return K(add_mod(x, o.x)); }
    K operator*(K o) const { return K(mul_mod(x, o.x)); }
    H operator-(K o) const
    {
        K a = *this + ~o.x;
        return a.x + !~a.x;
    }
};
const K C = 3006703054056749ULL;
const K Cinv = 15022799962985236769ULL;

K kpow(K a, H b)
{
    if (b == 0)
        return 1;
    K res = kpow(a, b / 2);
    res = res * res;
    if (b & 1)
        res = res * a;
    return res;
}

T fix_ang(T a)
{
    while (a >= 2 * M_PI) {
        a -= 2 * M_PI;
    }
    while (a < 0) {
        a += 2 * M_PI;
    }
    return a;
}

K ah(K& a, H b, K c)
{
    a = a * c + b;
}

K rh(K& a, H b, K cpow)
{
    a = a - cpow * b;
}

K rhb(K& a, H b)
{
    a = a - b;
}

K ahb(K& a, H b, K cpow, K cinv)
{
    a = (a + cpow * b) * cinv;
}

const size_t MAXV = 100005;
int X[MAXV], Y[MAXV], angleID[MAXV];
T angles[MAXV];
pair<T, int> as[MAXV];

H S[2 * MAXV];

H d2(int i, int j)
{
    H dx = abs(X[i] - X[j]);
    H dy = abs(Y[i] - Y[j]);
    return dx * dx + dy * dy;
}

void code()
{
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }
    T prev = atan2(Y[0] - Y[N - 1], X[0] - X[N - 1]);
    for (int i = 0; i < N; i++) {
        T a = atan2(Y[(i + 1) % N] - Y[i], X[(i + 1) % N] - X[i]);
        angles[i] = fix_ang(a - prev);
        as[i] = make_pair(angles[i], i);
        prev = a;
    }
    sort(as, as + N);
    int idx = 0;
    for (int i = 0; i < N;) {
        int j = i;
        while (eq(as[i].first, as[j].first)) {
            angleID[as[j].second] = idx;
            j++;
        }
        i = j;
        idx++;
    }
#ifdef IB_DEBUG
    for (int i = 0; i < N; i++) {
        printf("%g %d\n", angles[i], angleID[i]);
    }
#endif
    for (int i = 0; i < N; i++) {
        S[2 * i] = angleID[i];
        S[2 * i + 1] = d2(i, (i + 1) % N);
    }
#ifdef IB_DEBUG
    for (int i = 0; i < 2 * N; i++) {
        printf("%llu\n", S[i]);
    }
#endif
    K hash1 = 0, hash2 = 0;
    for (int i = 1; i < N; i++) {
        ah(hash1, S[i], C);
    }
    for (int i = 2 * N - 1; i > N; i--) {
        ah(hash2, S[i], C);
    }
    K cpow = kpow(C, N - 1);
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (hash1.x == hash2.x)
            count++;
        // Need to add S[i+N] to the hash and remove S[i+1]
        ah(hash1, S[(i + N) % (2 * N)], C);
        rh(hash1, S[(i + 1) % (2 * N)], cpow);
        // Need to add S[i] to the hash and remove S[i-N+1]
        rhb(hash2, S[(i + N + 1) % (2 * N)]);
        ahb(hash2, S[i], cpow, Cinv);

#ifdef IB_DEBUG
        cout << hash1.x << " " << hash2.x << endl;
#endif
    }
    cout << count << endl;
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int i = 0; i < T; i++) {
        code();
    }
}
