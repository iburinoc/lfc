// https://oi.edu.pl/en/archive/pa/2007/bar

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

typedef vector<int> vi;

pair<vi, vi> compute(const vector<vector<int>>& G, int i, int p)
{
    vector<int> ways;
    vector<int> opt;
    ways.push_back(INT_MAX);
    ways.push_back(0);
    for (auto c : G[i]) {
        if (c == p)
            continue;
        vi w1, o1;
        tie(w1, o1) = compute(G, c, i);
        while (opt.size() < o1.size() || opt.size() < w1.size()) {
            opt.push_back(INT_MAX);
        }
        for (int i = 0; i < o1.size(); i++) {
            opt[i] = min(o1[i], opt[i]);
        }
        for (int i = 0; i < w1.size(); i++) {
            if (w1[i] == INT_MAX)
                continue;
            opt[i] = min(w1[i] + 1, opt[i]);
        }
        vector<int> nways(w1.size() + ways.size() - 1, INT_MAX);
        for (int i = 1; i < ways.size(); i++) {
            if (i < ways.size()) {
                if (ways[i] != INT_MAX) {
                    nways[i] = min(ways[i] + 1, nways[i]);
                }
            }
            for (int j = 1; j < w1.size(); j++) {
                nways[i + j] = min(nways[i + j], ways[i] + w1[j]);
            }
        }
        swap(ways, nways);
    }
    return make_pair(ways, opt);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int N;
    cin >> N;

    vector<vector<int>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<int> a1, a2;
    tie(a1, a2) = compute(G, 0, -1);
    for (int i = 0; i < a1.size(); i++) {
        if (i >= a2.size()) {
            a2.push_back(a1[i]);
        } else {
            a2[i] = min(a2[i], a1[i]);
        }
    }

    int K;
    cin >> K;
    for (int i = 0; i < K; i++) {
        int q;
        cin >> q;
        cout << a2[q] << endl;
    }
}
