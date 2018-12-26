#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const size_t BUF_SIZE = 4096;

ll time_func(ll a, ll k, ll tu, ll td)
{
    return (a + k) * tu / 2 + (a - k) * td / 2;
}

int from_hex(char c)
{
    if (c >= 'a') {
        return c - 'a' + 10;
    } else {
        return c - '0';
    }
}

size_t fill_buf(char* buf, size_t num)
{
    return fread(buf, 1, num, stdin);
}

ll MUL = 800;

void code()
{
    ll N;
    scanf("%lld\n", &N);

    ll Np = N * 800LL;

    size_t rem = N / 2;

    char buf[BUF_SIZE];
    uint16_t stream = 0;
    size_t bits = 0;
    size_t buf_idx = BUF_SIZE;

    ll a = 0, k = 0;
    ll a1 = 0, k1 = 0;
    ll ans = 0;
    int mode = 0;

    while (a / MUL < 2 * N) {
        if (bits == 0) {
            if (buf_idx == BUF_SIZE) {
                buf_idx = 0;
                fill_buf(buf, min(BUF_SIZE, rem));
                rem -= min(BUF_SIZE, rem);
            }
            stream = from_hex(buf[buf_idx++]);
            bits = 4;
        }
        ll b = (stream & 0x8) ? 1 : -1;
        stream <<= 1;
        bits--;

        if (mode == 0) {
            ll eps = (6 * Np - k - 9 * a) / (9 + b);
            assert(eps >= 0);
            if (eps < MUL) {
                // intersection is here
                a1 = a + eps;
                k1 = k + b * eps;
                mode = 1;
            }
        } else if (mode == 1) {
            ll eps = (12 * Np + 9 * a1 - 9 * a + k - k1) / (9 - b);
            ll a2 = a + eps;
            ll k2 = k + b * eps;
            assert(eps >= 0);
            if (eps < MUL) {
                ans = (3 * (a1 + a2) + (k1 + k2)) / 4;
                mode = 2;
            }
        }
        a += 800;
        k += b * 800;
        assert(a / MUL <= 2 * N);
    }
    ll g = __gcd(ans, MUL);
    cout << (ans / g) << "/" << (MUL / g) << endl;
    // read newline
    fill_buf(buf, 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int t;
    scanf("%d\n", &t);
    for (int i = 0; i < t; i++)
        code();
}
