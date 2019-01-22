// https://oi.edu.pl/en/archive/oi/17/gil

#include <bits/stdc++.h>

using namespace std;

void nie()
{
    printf("NIE\n");
    exit(0);
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<vector<int>> G(N);
    vector<int> A(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        u--;
        v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 0; i < N; i++) {
        if (A[i] != 0)
            continue;
        if (G[i].size() == 0) {
            nie();
        }
        A[i] = 1;
        for (auto c : G[i]) {
            A[c] = 2;
        }
    }
    printf("TAK\n");
    for (int i = 0; i < N; i++) {
        printf("%c\n", "NSK"[A[i]]);
    }
}
