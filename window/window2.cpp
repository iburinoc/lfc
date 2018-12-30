// https://oi.edu.pl/en/archive/oi/5/okn

#include <bits/stdc++.h>

using namespace std;

struct Cross {
    Cross *cross, *next;
    int x, y;
    bool vis;
};

Cross C[6000];
int X1, Y1, X2, Y2;

bool inside(int x, int y)
{
    return X1 < x && x < X2 && Y1 < y && y < Y2;
}

int getWN(int x, int y)
{
    int base = 0;
    if (y == Y1) {
        return x - X1;
    }
    base += X2 - X1;
    if (x == X2) {
        return base + y - Y1;
    }
    base += Y2 - Y1;
    if (y == Y2) {
        return base + X2 - x;
    }
    return base + X2 - X1 + Y2 - y;
}

typedef pair<int, int> pii;
vector<pii> getCrossings(pii a, pii b)
{
    assert(a != b);
    vector<pii> res;
    if (a.first == b.first) {
        if (a.first <= X1 || a.first >= X2)
            return res;
        int miny = min(a.second, b.second);
        int maxy = max(a.second, b.second);
        if (miny <= Y1 && maxy > Y1) {
            res.emplace_back(a.first, Y1);
        }
        if (miny < Y2 && maxy >= Y2) {
            res.emplace_back(a.first, Y2);
        }
        if (a.second > b.second) {
            reverse(res.begin(), res.end());
        }
    }
    if (a.second == b.second) {
        if (a.second <= Y1 || a.second >= Y2)
            return res;
        int minx = min(a.first, b.first);
        int maxx = max(a.first, b.first);
        if (minx <= X1 && maxx > X1) {
            res.emplace_back(X1, a.second);
        }
        if (minx < X2 && maxx >= X2) {
            res.emplace_back(X2, a.second);
        }
        if (a.first > b.first) {
            reverse(res.begin(), res.end());
        }
    }
    return res;
}

int main()
{
    scanf("%d %d %d %d", &X1, &Y1, &X2, &Y2);
    swap(Y1, Y2);
    int N;
    scanf("%d", &N);
    vector<int> X(N);
    vector<int> Y(N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
    }

    vector<pii> crossings;
    int px = X[N - 1], py = Y[N - 1];
    for (int i = 0; i < N; i++) {
        int nx = X[i], ny = Y[i];
        auto res = getCrossings(pii(px, py), pii(nx, ny));
        crossings.insert(crossings.end(), res.begin(), res.end());
        if (res.size() == 0) {
            assert(inside(px, py) == inside(nx, ny));
        }
        if (res.size() == 1) {
            assert(inside(px, py) != inside(nx, ny));
        }
        if (res.size() == 2) {
            assert(inside(px, py) == false && inside(nx, ny) == false);
        }
        px = nx;
        py = ny;
    }
#ifdef IB_DEBUG
    for (auto p : crossings) {
        cout << p.first << " " << p.second << endl;
    }
#endif

    if (crossings.size() == 0) {
        if (inside(X[0], Y[0])) {
            printf("1\n");
            return 0;
        }
        int count = 0;
        double x = X1 + 0.5;
        double y = Y1 + 0.5;
        for (int i = 0; i < N; i++) {
            int x1 = X[i], x2 = X[(i + 1) % N];
            int y1 = Y[i], y2 = Y[(i + 1) % N];
            if (x1 != x2)
                continue;
            if (x1 < x)
                continue;
            if (min(y1, y2) < y && max(y1, y2) > y)
                count++;
        }
        printf("%d\n", count % 2);
        return 0;
    }

    vector<Cross*> cr;
    int p = inside(X[0], Y[0]);
    for (int i = 0; i < crossings.size(); i++) {
        tie(C[i].x, C[i].y) = crossings[i];
        C[i].next = nullptr;
        C[i].cross = nullptr;
        C[i].vis = false;
        if (p == 0) {
            C[i].cross = &C[(i + 1) % crossings.size()];
        }
        p = !p;
        cr.push_back(&C[i]);
    }
    assert(cr.size() % 2 == 0);
    sort(cr.begin(), cr.end(), [](const Cross* a, const Cross* b) {
        return getWN(a->x, a->y) < getWN(b->x, b->y);
    });

    for (int i = 0; i < cr.size(); i++) {
        cr[i]->next = cr[(i + 1) % cr.size()];
    }
    int num = 0;
    for (int i = 0; i < cr.size(); i++) {
        if (C[i].vis)
            continue;
        num++;
        Cross* cur = &C[i];
        while (!cur->vis) {
            cur->vis = true;
            if (cur->cross) {
                cur = cur->cross;
            } else {
                cur = cur->next;
            }
        }
    }
    printf("%d\n", num);
}
