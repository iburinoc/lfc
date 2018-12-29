// https://oi.edu.pl/en/archive/oi/5/okn
// Doesn't quite pass in time for all of the inputs because the judge is slow
// Would be fast enough on real contest, but is not as clean as intended solution

#include <bits/stdc++.h>

using namespace std;

const size_t MAXX = 2600;
typedef bitset<MAXX> row;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

int main()
{
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    swap(y1, y2);
    int N;
    scanf("%d", &N);
    vector<int> X(N);
    vector<int> Y(N);
    set<int> Xs;
    set<int> Ys;
    Xs.insert(x1);
    Xs.insert(x2);
    Ys.insert(y1);
    Ys.insert(y2);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &X[i], &Y[i]);
        Xs.insert(X[i]);
        Ys.insert(Y[i]);
    }
    unordered_map<int, int> mx, my;
    int i = 0;
    for (auto v : Xs) {
        mx[v] = i++;
    }
    int maxX = i;
    i = 0;
    for (auto v : Ys) {
        my[v] = i++;
    }
    int maxY = i;
    assert(maxX < MAXX);
    for (int i = 0; i < N; i++) {
        X[i] = mx[X[i]];
        Y[i] = my[Y[i]];
    }
    x1 = mx[x1];
    x2 = mx[x2];
    y1 = my[y1];
    y2 = my[y2];

    vector<tiii> ED;
    for (int i = 0; i < N; i++) {
        int a = i;
        int b = (i + 1) % N;
        if (X[a] != X[b])
            continue;
        ED.push_back(tiii(X[a], min(Y[a], Y[b]), max(Y[a], Y[b])));
    }
    sort(ED.begin(), ED.end());

    auto start = clock();
    vector<row> map(y2 - y1);
    const int xs = x2 - x1;
    for (int r = 0; r < map.size(); r++) {
        int cur = 0;
        int x = x1;
        int i = 0;
        int pr = r + y1;
        while (x < x2) {
            while (i < ED.size() && get<0>(ED[i]) <= x) {
                if (pr >= get<1>(ED[i]) && pr < get<2>(ED[i]))
                    cur = !cur;
                i++;
            }
            map[r][x - x1] = cur;
            x++;
        }
    }
    //cerr << (clock() - start) / (double)CLOCKS_PER_SEC << endl;

    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, 1, -1 };
    int count = 0;
    for (int r = 0; r < map.size(); r++) {
        for (int c = 0; c < xs; c++) {
            if (!map[r][c])
                continue;
            queue<int> Rq;
            queue<int> Cq;
            Rq.push(r);
            Cq.push(c);
            while (!Rq.empty()) {
                int r = Rq.front();
                int c = Cq.front();
                Rq.pop();
                Cq.pop();
                for (int i = 0; i < 4; i++) {
                    int nr = r + dy[i];
                    int nc = c + dx[i];
                    if (nr < 0 || nr >= map.size() || nc < 0 || nc >= xs)
                        continue;
                    if (!map[nr][nc])
                        continue;
                    map[nr][nc] = 0;
                    Rq.push(nr);
                    Cq.push(nc);
                }
            }
            count++;
        }
    }
    //cerr << (clock() - start) / (double)CLOCKS_PER_SEC << endl;
    //cerr << Xs.size() << " " << Ys.size() << endl;
    cout << count << endl;
}
