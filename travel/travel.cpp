// https://oi.edu.pl/en/archive/pa/2006/biu
// Note: haven't been able to find official input for this,
// the judge just tests against predetermined inputs

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

struct MaxFlow {
    struct Edge {
        int to, cap, flo;
        Edge* rev;
    };
    vector<forward_list<Edge>> adj;
    vector<Edge*> pre;
    vector<int> lim;
    queue<int> que;

    MaxFlow(int n)
        : adj(n)
        , pre(n)
        , lim(n)
    {
    }

    void add_edge(int st, int ed, int cap, int rev_cap = 0)
    {
        adj[st].push_front({ ed, cap, 0, 0 });
        adj[ed].push_front({ st, rev_cap, 0, 0 });
        adj[st].front().rev = &adj[ed].front();
        adj[ed].front().rev = &adj[st].front();
    }

    int go(int src, int sink)
    {
        int res = 0;
        while (1) {
            fill(pre.begin(), pre.end(), nullptr);
            lim[src] = 1 << 30, que.push(src);
            while (!que.empty()) {
                int at = que.front();
                que.pop();
                for (auto& e : adj[at]) {
                    if (e.to != src && !pre[e.to] && e.flo < e.cap) {
                        lim[e.to] = min(lim[at], e.cap - e.flo);
                        pre[e.to] = &e, que.push(e.to);
                    }
                }
            }
            if (!pre[sink])
                break;
            res += lim[sink];
            for (auto e = pre[sink]; e; e = pre[e->rev->to]) {
                e->flo += lim[sink], e->rev->flo -= lim[sink];
            }
        }
        return res;
    }
};

int main()
{
    int N;
    scanf("%d", &N);
    const int SINK = N;
    const int SOURCE = N + 1;
    MaxFlow mf(N + 2);

    int profit = 0;
    for (int i = 0; i < N; i++) {
        int x, k;
        scanf("%d %d", &x, &k);
        if (x >= 0) {
            mf.add_edge(SOURCE, i, x);
            profit += x;
        } else {
            mf.add_edge(i, SINK, -x);
        }

        for (int j = 0; j < k; j++) {
            int a, b;
            scanf("%d %d", &a, &b);
            a--;
            mf.add_edge(i, a, b);
        }
    }
    int cost = mf.go(SOURCE, SINK);
#ifdef IB_DEBUG
    cout << profit << " " << cost << " " << profit - cost << endl;
#endif
    vector<bool> vis(N + 2);
    queue<int> q;
    vis[SOURCE] = true;
    q.push(SOURCE);
    int out = 0;
    while (!q.empty()) {
        int i = q.front();
        q.pop();
        for (auto& e : mf.adj[i]) {
            if (e.flo >= e.cap)
                continue;
            if (vis[e.to])
                continue;
            q.push(e.to);
            vis[e.to] = true;
            out++;
        }
    }
    assert(!vis[SINK]);
    printf("%d\n", out);
    bool first = true;
    for (int i = 0; i < N; i++) {
        if (!vis[i])
            continue;
        if (!first) {
            printf(" ");
        }
        printf("%d", i + 1);
        first = false;
    }
    printf("\n");
}
