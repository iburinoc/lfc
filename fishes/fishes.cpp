// https://oi.edu.pl/en/archive/pa/2009/ryb

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, bool> pib;

typedef vector<int> vi;
typedef vector<pib> vpib;

#define sz(s) ((s).size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)

typedef long long int ll;

template <class T>
vector<T> cct(vector<T> a, const vector<T>& b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

vi min_cyclic_string(vi s)
{
    s = cct(s, s);
    int n = s.size();
    int i = 0, ans = 0;
    while (i < n / 2) {
        ans = i;
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j])
                k = i;
            else
                k++;
            j++;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    vi res(s.begin() + ans, s.begin() + ans + n / 2);
    return res;
}

struct VIHash {
    size_t operator()(const std::vector<int>& v) const
    {
        std::hash<int> hasher;
        size_t seed = 0;
        for (int i : v) {
            seed = seed * 3006703054056749 + hasher(i);
        }
        return seed;
    }
};

template <class InputIterator>
vi stringify(InputIterator first, InputIterator last)
{
    vi out;
    while (first != last) {
        out.push_back(first->first * 2 + first->second);
        first++;
    }
    return out;
}

pib cmpl(const pib a)
{
    return pib(a.first, !a.second);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int C, R;
    cin >> C >> R;
    vector<string> M(R);
    for (int i = 0; i < R; i++) {
        cin >> M[i];
    }
    vector<vector<int>> I(R, vector<int>(C, -1));

    int idx = 1;
    bool used = false;
    for (int r = 0; r < R; r++) {
        for (int c = 0; c < C; c++) {
            if (M[r][c] == '#') {
                if (used) {
                    idx++;
                    used = false;
                }
                continue;
            }
            I[r][c] = idx;
            used = true;
        }
        idx++;
        used = false;
    }
#if IB_DEBUG
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cout << setw(4) << I[i][j];
        }
        cout << endl;
    }
#endif

    int T;
    cin >> T;

    unordered_map<char, int> dr = {
        { 'N', -1 },
        { 'S', 1 },
    };
    unordered_map<char, int> dc = {
        { 'W', -1 },
        { 'E', 1 },
    };

    unordered_map<vi, int, VIHash> classes;
    vector<vector<int>> routes;
    for (int t = 0; t < T; t++) {
        int c, r, l;
        cin >> c >> r >> l;
        c--;
        r--;
        string s;
        cin >> s;
        assert(s.size() == l);
        deque<pib> route;

        for (int i = 0; i < s.size(); i++) {
            pib p(-1, false);
            char d = s[i];
            if (d == 'N') {
                p = pib(I[r][c], false);
            }
            c += dc[d];
            r += dr[d];
            if (d == 'S') {
                p = pib(I[r][c], true);
            }
            if (dr[d]) {
                assert(p.first > 0);
                if (!route.empty() && cmpl(route.back()) == p) {
                    route.pop_back();
                } else {
                    route.push_back(p);
                }
            }
        }
        while (!route.empty() && route.front() == cmpl(route.back())) {
            route.pop_back();
            route.pop_front();
        }
        vi lmce;
        if (!route.empty()) {
            vi rs = stringify(route.begin(), route.end());
            lmce = min_cyclic_string(rs);
        }
        auto it = classes.find(lmce);
        if (it != classes.end()) {
            routes[it->second].push_back(t);
        } else {
            classes[lmce] = routes.size();
            routes.push_back(vi(1, t));
        }
#if IB_DEBUG
        for (auto p : route) {
            cout << p.first << (p.second ? 'D' : 'U') << " ";
        }
        cout << endl;
#endif
    }
    cout << classes.size() << endl;
    for (int i = 0; i < routes.size(); i++) {
        cout << routes[i][0] + 1;
        if (i > 0)
            assert(routes[i][0] > routes[i - 1][0]);
        for (int j = 1; j < routes[i].size(); j++) {
            cout << " " << routes[i][j] + 1;
            assert(routes[i][j] > routes[i][j - 1]);
        }
        cout << endl;
    }
}
