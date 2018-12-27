// https://oi.edu.pl/en/archive/oi/9/nar

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

struct PHash {
    size_t operator()(const pii& p) const
    {
        std::hash<int> h;
        const size_t prime = 3006703054056749;
        return prime * h(p.first) + h(p.second);
    }
};

int main()
{
    int N;
    cin >> N;
    vector<vector<int>> G(N + 1);
    vector<vector<int>> iG(N + 1);
    vector<pii> E;
    unordered_map<pii, int, PHash> I;
    for (int i = 1; i < N; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int t;
            cin >> t;
            G[i].push_back(t);
            I[pii(i, t)] = E.size();
            E.push_back(pii(i, t));
        }
    }
    vector<int> LF(E.size(), -1);
    vector<int> RF(E.size(), -1);

    int cur = 1;
    const int WF = 0;
    const int EF = 1;
    while (cur != N) {
        assert(G[cur].size() > 0);
        LF[I[pii(cur, G[cur][0])]] = WF;
        cur = G[cur][0];
    }
    cur = 1;
    while (cur != N) {
        const auto& C = G[cur];
        assert(C.size() > 0);
        RF[I[pii(cur, C[C.size() - 1])]] = EF;
        cur = C[C.size() - 1];
    }
    int fidx = 2;
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < G[i].size() - 1; j++) {
            unordered_set<int> LV;
            int cur = G[i][j];
            while (true) {
                LV.insert(cur);
                if (cur == N)
                    break;
                cur = G[cur][G[cur].size() - 1];
            }
            cur = G[i][j + 1];
            LF[I[pii(i, cur)]] = fidx;
            while (LV.count(cur) == 0) {
                int ncur = G[cur][0];
                LF[I[pii(cur, ncur)]] = fidx;
                cur = ncur;
            }
            int end = cur;
            cur = G[i][j];
            RF[I[pii(i, cur)]] = fidx;
            while (cur != end) {
                int ncur = G[cur][G[cur].size() - 1];
                RF[I[pii(cur, ncur)]] = fidx;
                cur = ncur;
            }
            fidx++;
        }
    }
#ifdef IB_DEBUG
    cout << fidx << endl;
#endif

    vector<set<int>> FG(fidx);
    for (int i = 0; i < E.size(); i++) {
        FG[LF[i]].insert(RF[i]);
    }
    vector<int> sources(fidx, 0);
    for (int i = 0; i < FG.size(); i++) {
        for (auto c : FG[i]) {
            sources[c]++;
        }
    }
    queue<int> ready;
    ready.push(WF);
    vector<int> MD(fidx, 0);
    while (!ready.empty()) {
        int i = ready.front();
        ready.pop();
        int d = MD[i];
        assert(sources[i] == 0);
        for (auto c : FG[i]) {
            MD[c] = max(MD[c], d + 1);
            sources[c]--;
            assert(sources[c] >= 0);
            if (sources[c] == 0) {
                ready.push(c);
            }
        }
    }
    cout << MD[EF] << endl;
}
