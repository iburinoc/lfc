// https://oi.edu.pl/en/archive/pa/2011/kan

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

void insert(set<pii>& I, multiset<int>& L, int v)
{
    int l = v;
    int r = v;
    auto it = I.lower_bound(pii(v, 0));
    if (it != I.end()) {
        assert(it->first > v);
    }
    if (it != I.begin()) {
        auto il = it;
        il--;
        assert(il->second < l);
        if (il->second + 1 == l) {
            l = il->first;
            L.erase(L.find(il->second - il->first + 1));
            I.erase(il);
        }
    }
    if (it != I.end() && it->first == r + 1) {
        r = it->second;
        L.erase(L.find(it->second - it->first + 1));
        I.erase(it);
    }
    I.insert(pii(l, r));
    L.insert(r - l + 1);
}

void remove(set<pii>& I, multiset<int>& L, int v)
{
    auto it = I.upper_bound(pii(v, INT_MAX));
    it--;
    int l = it->first;
    int r = it->second;
    assert(l <= v && r >= v);
    L.erase(L.find(r - l + 1));
    I.erase(it);
    if (v > l) {
        L.insert(v - l);
        I.insert(pii(l, v - 1));
    }
    if (v < r) {
        L.insert(r - v);
        I.insert(pii(v + 1, r));
    }
}

int getMax(const multiset<int>& l)
{
    if (l.empty())
        return 0;
    return *l.crbegin();
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<pii> Vs;
    vector<int> A(N), B(N), C(M), D(M);
    vector<int> V(2 * N);
    vector<int> Xi(2 * N, -1), Yi(2 * N, -1);
    for (int i = 0; i < N; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        V[2 * i] = a;
        V[2 * i + 1] = b;
        Vs.push_back(pii(a, 2 * i));
        Vs.push_back(pii(b, 2 * i + 1));
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &C[i], &D[i]);
    }
    sort(Vs.begin(), Vs.end());
    for (int i = 0; i < Vs.size(); i++) {
        int idx = Vs[i].second;
        V[idx] = i;
        if (idx % 2) {
            Yi[i] = idx / 2;
        } else {
            Xi[i] = idx / 2;
        }
    }
    for (int i = 0; i < M; i++) {
        auto it = lower_bound(Vs.begin(), Vs.end(), pii(C[i], 0));
        if (it == Vs.end()) {
            C[i] = 2 * N + 1;
        } else {
            C[i] = V[it->second];
        }
        it = upper_bound(Vs.begin(), Vs.end(), pii(D[i], INT_MAX));
        if (it == Vs.begin()) {
            D[i] = -1;
        } else {
            it--;
            D[i] = V[it->second];
        }
    }

    int sqr = 1;
    while (sqr * sqr < M && sqr < 2 * N)
        sqr++;
    int bsize = 2 * N / sqr;
    int bucket_count = 2 * N / bsize + 2;
    vector<vector<pii>> buckets(bucket_count);
    for (int i = 0; i < M; i++) {
        assert(C[i] >= 0);
        int bnum = C[i] / bsize;
        buckets[bnum].push_back(pii(D[i], i));
    }
    set<pii> inter;
    multiset<int> len;

    vector<int> ans(M);
    int cc = -1, cd = -1;
    vector<bool> in(N, false);
    for (int i = 0; i < buckets.size(); i++) {
        sort(buckets[i].begin(), buckets[i].end());
        for (auto p : buckets[i]) {
            int idx = p.second;
            int c = C[idx];
            int d = D[idx];
            while (cc != c || cd != d) {
                int oldIdx = -1, newIdx = -1;
                if (cc != c) {
                    if (cc >= 0 && cc < Yi.size())
                        oldIdx = Yi[cc];
                    if (cc < c)
                        cc++;
                    else
                        cc--;
                    if (cc >= 0 && cc < Yi.size())
                        newIdx = Yi[cc];
                } else {
                    if (cd >= 0 && cd < Xi.size())
                        oldIdx = Xi[cd];
                    if (cd < d)
                        cd++;
                    else
                        cd--;
                    if (cd >= 0 && cd < Xi.size())
                        newIdx = Xi[cd];
                }
                vector<int> tp{ oldIdx, newIdx };
                for (auto v : tp) {
                    if (v == -1)
                        continue;
                    bool inside = cc <= V[2 * v + 1] && cd >= V[2 * v];
                    if (in[v] && !inside) {
                        in[v] = false;
                        remove(inter, len, v);
                    } else if (!in[v] && inside) {
                        in[v] = true;
                        insert(inter, len, v);
                    }
                }
            }
            ans[idx] = getMax(len);
        }
    }
    for (int i = 0; i < M; i++) {
        printf("%d\n", ans[i]);
    }
}
