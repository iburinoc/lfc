// http://oi.edu.pl/en/archive/pa/2010/cuk

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef pair<ll, ll> pii;
typedef pair<pii, bool> piib;

ll ipow(ll a, ll b)
{
    ll p = 1;
    for (ll i = 0; i < b; i++) {
        p *= a;
    }
    return p;
}

int main()
{
    ll N;
    cin >> N;
    vector<ll> A(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }

    ll MM1 = ipow(3, N / 2);
    ll MM2 = ipow(3, (N + 1) / 2);

    vector<piib> P;
    for (ll m = 0; m < MM1; m++) {
        ll s[3];
        memset(s, 0, sizeof(s));
        ll cm = m;
        for (ll i = 0; i < N / 2; i++) {
            s[cm % 3] += A[i];
            cm /= 3;
        }
        P.push_back(piib(pii(s[0] - s[1], s[1] - s[2]), true));
    }
    for (ll m = 0; m < MM2; m++) {
        ll s[3];
        memset(s, 0, sizeof(s));
        ll cm = m;
        for (ll i = 0; i < (N + 1) / 2; i++) {
            s[cm % 3] += A[i + N / 2];
            cm /= 3;
        }
        P.push_back(piib(pii(s[1] - s[0], s[2] - s[1]), false));
    }

    sort(P.begin(), P.end(), [](const piib& a, const piib& b) {
        if (a.first.second != b.first.second) {
            return a.first.second < b.first.second;
        } else if (a.first.first != b.first.first) {
            return a.first.first < b.first.first;
        } else {
            return a.second < b.second;
        }
    });

    map<ll, ll> S;
    ll best = INT_MAX;
    for (const auto& v : P) {
        pii p = v.first;
        if (v.second) {
            auto it = S.upper_bound(p.first);
            if (it == S.begin())
                continue;
            it--;
            assert(p.first >= it->first && p.second >= it->second);
            ll val = p.first - it->first + p.second - it->second;
            best = min(best, val);
        } else {
            S[p.first] = p.second;
            auto it = S.find(p.first);
            it++;
            while (true) {
                if (it == S.end())
                    break;
                if (it->first + it->second > p.first + p.second)
                    break;
                it = S.erase(it);
            }
        }
    }
    cout << best << endl;
}
