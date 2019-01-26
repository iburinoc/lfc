// https://oi.edu.pl/en/archive/pa/2011/pal

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

pii dfs(int i, int p, vector<vector<int>>& G)
{
    int maxD = 0;
    int maxC[3];
    memset(maxC, 0, sizeof(maxC));
    for (auto c : G[i]) {
        if (c == p)
            continue;
        int D, C;
        tie(D, C) = dfs(c, i, G);
        maxD = max(maxD, D);
        maxC[0] = C;
        sort(maxC, maxC + 3);
    }
    maxD = max(maxD, maxC[1] + maxC[2]);
    return pii(maxD, maxC[2] + 1);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<vector<int>> G(N);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int D = dfs(0, -1, G).first;
    int ans;
    if (M <= D) {
        ans = M + 1;
    } else if (M >= (2 * N - D - 2)) {
        ans = N;
    } else {
        ans = (M + D + 2) / 2;
    }
    printf("%d\n", ans);
}
