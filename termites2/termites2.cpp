// https://oi.edu.pl/en/archive/pa/2010/ted

#include <bits/stdc++.h>

using namespace std;

int N;

struct VS {
    bool S[2];
    int MC[2];
    vector<int> ch;
    int sz;
    int par;

    VS(int i)
    {
        S[0] = true;
        S[1] = true;
        MC[0] = 0;
        MC[1] = 0;
        sz = 1;
        par = i;
    }
};

vector<VS> T;

int find(int x)
{
    while (T[x].par != x) {
        x = T[x].par;
    }
    return x;
}

void join(int a, int b)
{
    a = find(a);
    b = find(b);
    if (T[a].sz < T[b].sz) {
        swap(a, b);
    }
    T[a].ch.push_back(b);
    T[a].sz += T[b].sz;
    T[b].par = a;
}

void clear(int p, int n)
{
    auto& Q = T[n];
    for (; Q.MC[p] < Q.ch.size(); Q.MC[p]++) {
        clear(p, Q.ch[Q.MC[p]]);
    }

    T[n].S[p] = false;
}

int main()
{
    scanf("%d", &N);
    T.reserve(N);
    for (int i = 0; i < N; i++) {
        T.push_back(VS(i));
    }
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--;
        v--;
        int p = i & 1;

        int pu = find(u), pv = find(v);
        if (T[u].S[p] && T[v].S[p]) {
            // merge them, we can clear everything from the other player
            // either of the two values can be kept alive if need be
            clear(!p, pu);
            clear(!p, pv);
            join(pu, pv);
            continue;
        }
        if (T[v].S[p]) {
            swap(u, v);
            swap(pu, pv);
        }
        if (T[u].S[p]) {
            // v isn't available, we have to clear u, this means that we need to clear u's component from both players
            clear(p, pu);
            clear(!p, pu);
            T[v].S[!p] = false;
            join(pu, pv);
            continue;
        }
        // This player loses
        printf("%d\n", i + 1);
        return 0;
    }
    printf("-1\n");
}
