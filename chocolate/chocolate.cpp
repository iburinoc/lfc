// http://oi.edu.pl/en/archive/oi/10/cze

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

vector<ll> X;

const int MAX = 2050;
const int MAXS = 12;
ll rmq[2 * MAX][MAXS];
ll ms[MAX];

ll query(ll l, ll r) {
    ll s = ms[r - l];
    ll i1 = rmq[l][s];
    ll i2 = rmq[r-(1<<s)][s];
    return X[i1] > X[i2] ? i1 : i2;
}

ll solve(ll lx, ll rx, ll ly, ll ry) {
    if (lx >= rx && ly >= ry) return 0;
    ll mc = lx < rx ? query(lx, rx) : X.size()-1;
    ll mr = ly < ry ? query(ly, ry) : X.size()-1;
    ll mv;
    if (X[mr] > X[mc]) {
        mc = -1;
        mv = X[mr];
    } else {
        mr = -1;
        mv = X[mc];
    }

    ll res = mv;
    if (mc != -1) {
        // split on mc
        res += solve(lx, mc, ly, ry);
        res += solve(mc+1, rx, ly, ry);
    } else {
        res += solve(lx, rx, ly, mr);
        res += solve(lx, rx, mr+1, ry);
    }
    return res;
}

int main() {
    ll M, N;
    cin >> M >> N;
    ll K = M + N - 2;

    for (int i = 0; i < M-1; i++) {
        ll x;
        cin >> x;
        X.push_back(x);
    }
    for (int i = 0; i < N-1; i++) {
        ll x;
        cin >> x;
        X.push_back(x);
    }
    int p = 0;
    for (int i = 1; i < MAX; i++) {
        if (i >= 1 << (p+1)) p++;
        ms[i] = p;
    }
    for (int i = 0; i < X.size(); i++) {
        rmq[i][0] = i;
    }
    for (int s = 1; s < MAXS; s++) {
        ll len = 1LL << s;
        for (int i = 0; i < X.size(); i++) {
            ll s1 = rmq[i][s-1];
            ll s2 = rmq[i+len/2][s-1];
            if (X[s1] > X[s2]) {
                rmq[i][s] = s1;
            } else {
                rmq[i][s] = s2;
            }
        }
    }
    X.push_back(0);
    cout << solve(0, M-1, M-1, M+N-2) << endl;
}
