// https://oi.edu.pl/en/archive/pa/2010/pol

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;
typedef ld T;
typedef complex<T> Pt;

int N, M;
vector<Pt> P;

vector<vector<int>> A;
vector<vector<int>> R;

const T tau = 2 * M_PI;

T fixAng(T a)
{
    if (a < 0) {
        return a + tau;
    }
    return a;
}

T cross(Pt a, Pt b)
{
    return imag(conj(a) * b);
}

inline bool inBounds(T lo, T hi, T c)
{
    if (hi < lo)
        hi += 2 * M_PI;
    if (c < lo)
        c += 2 * M_PI;
    return c < hi;
}

inline int B(int x, int y, int z)
{
    assert(cross(P[z] - P[x], P[y] - P[x]) < 0);
    int a1 = R[x][z], a2 = R[x][y];
    if (a1 >= a2) {
        return a1 - a2 - 1;
    }
    return (N - 2) + a1 - a2;
}

int main()
{
    scanf("%d %d", &N, &M);
    P.resize(N);

    A = vector<vector<int>>(N, vector<int>(N));
    R = vector<vector<int>>(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        P[i] = Pt(x, y);
    }

    vector<pair<T, int>> L;
    L.reserve(N - 1);
    for (int i = 0; i < N; i++) {
        L.clear();
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            T a = fixAng(arg(P[j] - P[i]));
            L.push_back(make_pair(a, j));
        }
        sort(L.begin(), L.end());
        int op = 1;
        for (int k = 0; k < L.size(); k++) {
            while (op != k) {
                T target = L[op].first + ((op < k) ? tau : 0);
                if (target > L[k].first + M_PI)
                    break;
                op = (op + 1) % L.size();
            }
            A[i][L[k].second] = (op - k - 1 + N - 1) % (N - 1);
            R[i][L[k].second] = k;
        }
    }
    vector<int> poly;
    for (int m = 0; m < M; m++) {
        poly.clear();
        int K;
        scanf("%d", &K);
        poly.reserve(K);
        int a0, prev;
        scanf("%d %d", &a0, &prev);
        a0--;
        prev--;
        int total = 0;
        poly.push_back(a0);
        poly.push_back(prev);

        for (int k = 2; k < K; k++) {
            int a;
            scanf("%d", &a);
            a--;
            T c = cross(P[prev] - P[a0], P[a] - P[a0]);
            int a1, a2, mul;
            if (c < 0) {
                a1 = prev;
                a2 = a;
                mul = 1;
            } else {
                a1 = a;
                a2 = prev;
                mul = -1;
            }
            int val = B(a0, a2, a1) + B(a2, a1, a0) + B(a1, a0, a2) + A[a0][a1] + A[a1][a2] + A[a2][a0] - 2 * (N - 3);
            total += mul * val;
            poly.push_back(a);
            prev = a;
        }
        const Pt& p0 = P[a0];
        for (int k = 1; k < K; k++) {
            const Pt& pc = P[poly[k]];
            const Pt& pl = P[poly[k - 1]];
            const Pt& ph = P[poly[(k + 1) % K]];
            T hi = arg(ph - pc);
            T lo = arg(pl - pc);
            T c = arg(pc - p0);
            if (inBounds(lo, hi, c))
                total--;
        }
        printf("%d\n", total);
    }
}
