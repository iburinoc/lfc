// https://oi.edu.pl/en/archive/ontak/2007/hip

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

vector<pii> merge(const vector<pii>& _c1, const vector<pii>& _c2)
{
    const vector<pii>*p1 = &_c1, *p2 = &_c2;
    bool odd = false;
    if (_c1.size() % 2 != 0) {
        if (_c2.size() % 2 == 0) {
            swap(p1, p2);
        } else {
            odd = true;
        }
    }
    const auto &c1 = *p1, &c2 = *p2;
    vector<pii> res;
    res.reserve(c1.size() * c2.size());
    for (int i = 0; i < c1.size(); i++) {
        int dir = 1;
        int start = 0;
        int end = c2.size() - odd - 1;
        int off = 0;
        if (i % 2 == 1) {
            dir = -1;
            start = c2.size() - odd - 1;
            end = 0;
            off = -1;
        }
        for (int j = start; j != end; j += dir) {
            pii m = c2[j + off];
            pii nm(m.first, m.second * dir);
            res.push_back(nm);
        }
        if (i != c1.size() - 1 || !odd) {
            res.push_back(c1[i]);
        }
    }
    if (odd) {
        res.push_back(c2[c2.size() - 2]);
        for (int i = c1.size() - 1; i > 0; i--) {
            pii m = c1[i - 1];
            pii nm(m.first, -m.second);
            res.push_back(nm);
        }
        res.push_back(c2[c2.size() - 1]);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int N;
    scanf("%d", &N);
    vector<int> K(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &K[i]);
    }

    vector<vector<pii>> C(N);
    for (int i = 0; i < N; i++) {
        vector<pii> nc(K[i]);
        for (int j = 0; j < K[i]; j++) {
            nc[j] = pii(i + 1, 1);
        }
        C[i] = nc;
    }
#if 0
    while (C.size() > 1) {
        vector<vector<pii>> NC;
        for (int i = 0; i < C.size(); i += 2) {
            if (i + 1 < C.size()) {
                NC.push_back(merge(C[i], C[i + 1]));
            } else {
                NC.push_back(C[i]);
            }
        }
        swap(NC, C);
    }
    const auto& cur = C[0];
#else
    vector<pii> cur = C[0];
    for (int i = 1; i < N; i++) {
        cur = merge(cur, C[i]);
    }
#endif
#ifdef IB_DEBUG
    vector<int> state(N, 0);
#endif
    for (auto p : cur) {
        printf("%d %d", p.first, p.second);
#ifdef IB_DEBUG
        state[p.first - 1] = (state[p.first - 1] + p.second + K[p.first - 1]) % K[p.first - 1];
        for (int i = 0; i < N; i++) {
            printf(" %d", state[i]);
        }
#endif
        printf("\n");
    }
}
