#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int main()
{
    int N;
    scanf("%d", &N);
    int a0;
    scanf("%d", &a0);
    vector<int> A(N - 1);
    vector<int> D(a0, INT_MAX);
    for (int i = 0; i < N - 1; i++) {
        scanf("%d", &A[i]);
    }

    set<pii> q;
    D[0] = 0;
    for (int i = 0; i < a0; i++) {
        q.insert(pii(D[i], i));
    }

    while (!q.empty()) {
        int dist, i;
        tie(dist, i) = *q.begin();
        if (dist == INT_MAX)
            break;
        q.erase(q.begin());
        for (int j = 0; j < N - 1; j++) {
            int ni = (i + A[j]) % a0;
            int ndist = dist + A[j];
            if (ndist < D[ni]) {
                q.erase(pii(D[ni], ni));
                D[ni] = ndist;
                q.insert(pii(ndist, ni));
            }
        }
    }

    int K;
    scanf("%d", &K);
    for (int k = 0; k < K; k++) {
        int b;
        scanf("%d", &b);
        if (D[b % a0] <= b) {
            printf("TAK\n");
        } else {
            printf("NIE\n");
        }
    }
}
