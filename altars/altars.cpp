// https://oi.edu.pl/en/archive/oi/6/olt
// Needed to do some constant optimization here:
// - Pull diffs outside of loop to reduce allocations
// - Remove asserts
// - Remove extra unnecessary comparisons
// - Use scanf/printf

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef ll T;
typedef complex<T> Pt;
typedef array<Pt, 5> rect;

static inline T cross(Pt a, Pt b)
{
    return imag(conj(a) * b);
}

static inline int c2(Pt a, Pt b)
{
    return -cross(Pt(a), Pt(b));
}

static inline bool compare(Pt a, Pt b)
{
    return c2(a, b) < 0;
}

static inline Pt rot(Pt a, int n)
{
    for (int j = 0; j < n; j++) {
        a = Pt(-a.imag(), a.real());
    }
    return a;
}

int main(int argc, char** argv)
{
    if (argc > 1) {
        freopen(argv[1], "rb", stdin);
    }
    int N;
    scanf("%d", &N);
    vector<Pt> BL(N);
    vector<Pt> TR(N);
    vector<rect> PTS(N);
    vector<char> D(N);
    for (int i = 0; i < N; i++) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d %c", &x1, &y2, &x2, &y1, &D[i]);
        BL[i] = Pt(x1, y1) * 4LL;
        TR[i] = Pt(x2, y2) * 4LL;
        rect r;
        r[0] = BL[i];
        r[2] = TR[i];
        r[1] = Pt(TR[i].real(), BL[i].imag());
        r[3] = Pt(BL[i].real(), TR[i].imag());
        r[4] = r[0];
        PTS[i] = r;
    }
    vector<int> res;
    unordered_map<char, int> fidx = {
        { 'S', 0 },
        { 'E', 1 },
        { 'N', 2 },
        { 'W', 3 },
    },
                             roti = {
                                 { 'S', 2 },
                                 { 'E', 1 },
                                 { 'N', 0 },
                                 { 'W', 3 },
                             };
    vector<pair<Pt, int>> diffs;
    for (int i = 0; i < N; i++) {
        diffs.clear();
        Pt mid = (BL[i] + TR[i]) / 2LL;
        int fi = fidx[D[i]];
        Pt e1 = (PTS[i][fi + 1] - PTS[i][fi]) / 4LL + PTS[i][fi];
        Pt e2 = (PTS[i][fi + 1] - PTS[i][fi]) * 3LL / 4LL + PTS[i][fi];
#ifdef IB_DEBUG
        cout << i << ": " << e1 << " " << e2 << endl;
#endif
        e1 -= mid;
        e2 -= mid;
        int r = roti[D[i]];
        e1 = rot(e1, r);
        e2 = rot(e2, r);
#ifdef IB_DEBUG
        cout << i << ": " << e1 << " " << e2 << endl;
#endif
        for (int j = 0; j < N; j++) {
            if (i == j)
                continue;
            Pt rpts[4];
            for (int d = 0; d < 4; d++) {
                rpts[d] = PTS[j][d] - mid;
            }
            sort(rpts, rpts + 4, compare);
            Pt p1 = rpts[0];
            Pt p2 = rpts[3];
            p1 = rot(p1, r);
            p2 = rot(p2, r);
            if (p1.imag() <= 0 && p2.imag() <= 0)
                continue;
            p1.imag(max(p1.imag(), 0LL));
            p2.imag(max(p2.imag(), 0LL));
            if (c2(p1, e2) >= 0)
                continue;
            if (c2(p2, e1) <= 0)
                continue;
#ifdef IB_DEBUG
            cout << "\t" << j << ": " << p1 << " " << 1 << endl;
            cout << "\t" << j << ": " << p2 << " " << -1 << endl;
#endif
            diffs.push_back(make_pair(p1, 1));
            diffs.push_back(make_pair(p2, -1));
        }
        sort(diffs.begin(), diffs.end(), [](const pair<Pt, int>& p1, const pair<Pt, int>& p2) {
            T c = c2(p1.first, p2.first);
            if (c != 0) {
                return c < 1;
            }
            return p1.second > p2.second;
        });
        int sum = 0;
        if (diffs.size() == 0)
            goto bad;
        for (auto p : diffs) {
            if (!compare(p.first, e2))
                break;
            if (sum == 0 && compare(e1, p.first)) {
                goto bad;
            }
            sum += p.second;
#ifdef IB_DEBUG
            cout << "\t" << p.first << " " << p.second << " " << sum << endl;
#endif
            if (sum == 0 && compare(e1, p.first)) {
                goto bad;
            }
        }
        continue;
    bad:
        res.push_back(i);
    }
    if (res.size() == 0) {
        printf("BRAK\n");
    } else {
        for (auto v : res) {
            printf("%d\n", v + 1);
        }
    }
}
