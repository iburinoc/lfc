// http://oi.edu.pl/en/archive/oi/10/mal

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

struct Element {
    int parent;
    int size;
    vector<int> children;
};

int SZ;
Element mks[200005];

void init(int n)
{
    SZ = n;
    for (int i = 0; i < n; i++) {
        mks[i].parent = i;
        mks[i].size = 1;
    }
}

int get(int a)
{
    assert(0 <= a && a < SZ);
    while (mks[a].parent != a) {
        a = mks[a].parent;
    }
    return a;
}

void join(int a, int b)
{
    assert(0 <= a && a < SZ);
    assert(0 <= b && b < SZ);
    a = get(a);
    b = get(b);
    if (a == b)
        return;
    if (mks[a].size < mks[b].size) {
        swap(a, b);
    }
    if (b == 0) {
        swap(a, b);
    }
    mks[b].parent = a;
    mks[a].size += mks[b].size;
    mks[a].children.push_back(b);
}

struct PairHash {
    size_t operator()(const pii& p) const
    {
        hash<int> h;
        return ((size_t)3006703054056749LL) * h(p.first) + h(p.second);
    }
};

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    vector<vector<int>> hands(N, vector<int>(2));
    vector<pii> drop(M);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &hands[i][0], &hands[i][1]);
        if (hands[i][0] > 0)
            hands[i][0]--;
        if (hands[i][1] > 0)
            hands[i][1]--;
    }
    unordered_set<pii, PairHash> cut;
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &(drop[i].first), &(drop[i].second));
        drop[i].first--;
        drop[i].second--;
        int a = drop[i].first;
        int b = hands[a][drop[i].second];
        if (b == -1)
            continue;
        cut.insert(pii(a, b));
    }

    init(N);
    // initialize state at T=M
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 2; j++) {
            if (hands[i][j] == -1)
                continue;
            int a = i;
            int b = hands[i][j];
            if (cut.find(pii(a, b)) != cut.end())
                continue;
            join(a, b);
        }
    }

    vector<int> res(N, -1);
    for (int i = M - 1; i >= 0; i--) {
        int a = drop[i].first;
        int b = hands[a][drop[i].second];
        if (b == -1)
            continue;
        a = get(a);
        b = get(b);
        if (a == b)
            continue;
        if (a > b) {
            swap(a, b);
        }
        if (a == 0) {
            // b is getting connected
            queue<int> q;
            q.push(b);
            while (!q.empty()) {
                int f = q.front();
                q.pop();
                assert(res[f] == -1);
                res[f] = i;
                for (auto c : mks[f].children) {
                    q.push(c);
                }
            }
        }
        join(a, b);
    }
    for (auto r : res) {
        printf("%d\n", r);
    }
}
