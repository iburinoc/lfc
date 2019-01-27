// https://oi.edu.pl/en/archive/oi/4/kaj

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int W, N;
    scanf("%d %d", &W, &N);
    vector<int> V(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &V[i]);
    }
    sort(V.begin(), V.end());
    int l = 0, r = N - 1;
    int ans = 0;
    while (l < r) {
        if (V[l] + V[r] <= W) {
            l++;
        }
        r--;
        ans++;
    }
    if (l == r)
        ans++;
    printf("%d\n", ans);
}
