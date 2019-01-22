// https://oi.edu.pl/en/archive/oi/16/lyz

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

const int MAXN = 270000;

ll N, M, K, D, S, P;

ll V[2 * MAXN];
ll MS[2 * MAXN];
ll PR[2 * MAXN];
ll PL[2 * MAXN];
ll SZ[2 * MAXN];

void build(ll id, ll sz)
{
    if (sz == 0)
        return;
    SZ[id] = sz;
    MS[id] = 0;
    PR[id] = 0;
    PL[id] = 0;
    V[id] = -K * sz;
    build(id * 2 + 1, sz / 2);
    build(id * 2 + 2, sz / 2);
}

static void add_st(ll id, ll r, ll v)
{
    V[id] += v;
    if (SZ[id] == 1) {
        MS[id] = max(0LL, V[id]);
        PR[id] = max(0LL, V[id]);
        PL[id] = max(0LL, V[id]);
        return;
    }
    ll lid = id * 2 + 1, rid = id * 2 + 2;
    if (r < SZ[id] / 2) {
        add_st(lid, r, v);
    } else {
        add_st(rid, r - SZ[id] / 2, v);
    }
    assert(V[id] == V[lid] + V[rid]);

    ll c0 = max(MS[rid], MS[lid]);
    ll c1 = max(V[id], PL[rid] + PR[lid]);
    MS[id] = max(c0, c1);
    PL[id] = max(PL[lid], V[lid] + PL[rid]);
    PR[id] = max(PR[rid], V[rid] + PR[lid]);
    assert(MS[id] >= PL[id]);
    assert(MS[id] >= PR[id]);
}

int main()
{
    scanf("%lld %lld %lld %lld", &N, &M, &K, &D);

    S = N - D;

    P = 1 << (sizeof(int) * 8 - __builtin_clz((int)S));
    build(0, P);

    for (int i = 0; i < M; i++) {
        ll r, x;
        scanf("%lld %lld", &r, &x);
        r--;
        assert(r < S);
        add_st(0, r, x);
        if (MS[0] > K * D) {
            printf("NIE\n");
        } else {
            printf("TAK\n");
        }
    }
}
