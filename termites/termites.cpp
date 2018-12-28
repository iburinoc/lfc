// http://oi.edu.pl/en/archive/pa/2010/ter
// Relevant paper: https://www.mimuw.edu.pl/~idziaszek/termity/termity.pdf

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

typedef vector<ll> vi;
typedef pair<vi, ll> result;

result apply_worthless(const vi& end, int parity)
{
    int mul = (parity % 2 == 0) ? 1 : -1;

    ll val = 0;
    deque<ll> res;
    for (int i = 0; i < end.size(); i++) {
        res.push_back(end[i]);
        while (true) {
            size_t s = res.size();
            if (s < 2)
                break;
            if (res[0] < res[1])
                break;
            val += mul * (res[1] - res[0]);
            res.pop_front();
            res.pop_front();
        }
    }
    vi out(res.begin(), res.end());
    for (int i = 0; i + 1 < out.size(); i++) {
        assert(out[i] <= out[i + 1]);
    }
    return result(out, val);
}

vi apply_fusion(const vi& end)
{
    vi out;
    for (int i = 0; i < end.size(); i++) {
        out.push_back(end[i]);
        while (true) {
            size_t s = out.size();
            if (s < 3)
                break;
            if (out[s - 3] > out[s - 2] || out[s - 1] > out[s - 2])
                break;
            ll nc = out[s - 3] + out[s - 1] - out[s - 2];
            out.pop_back();
            out.pop_back();
            out.pop_back();
            out.push_back(nc);
        }
    }
    auto mit = min_element(out.begin(), out.end());
    for (auto it = out.begin(); it != mit; it++) {
        assert(*it >= *(it + 1));
    }
    for (auto it = mit; (it + 1) != out.end(); it++) {
        assert(*it <= *(it + 1));
    }
    return out;
}

int main()
{
    ll N;
    scanf("%lld", &N);
    vector<ll> L(N);
    ll parity = 0;
    ll sum = 0;
    for (int i = 0; i < N; i++) {
        scanf("%lld", &L[i]);
        parity += L[i] != 0;
        sum += L[i];
    }
    parity %= 2;

    bool front = true;
    vi cur;
    vi outs;
    ll vals = 0;
    for (int i = 0; i <= N; i++) {
        if (i == N || L[i] == 0) {
            if (cur.size() > 0) {
                vi out = cur;
                ll val;
                if (i == N) {
                    reverse(out.begin(), out.end());
                }
                out = apply_fusion(out);
                if (front || i == N) {
                    ll val;
                    tie(out, val) = apply_worthless(out, parity);
                    vals += val;
                }
                outs.insert(outs.end(), out.begin(), out.end());
                cur.clear();
            }
            front = false;
        } else {
            cur.push_back(L[i]);
        }
    }
    sort(outs.begin(), outs.end());
    reverse(outs.begin(), outs.end());
    for (int i = 0; i < outs.size(); i++) {
        vals += ((i % 2 == 0) ? 1 : -1) * outs[i];
    }
    ll a = (vals + sum) / 2;
    ll b = (sum - vals) / 2;
    assert(a + b == sum);
    assert(a - b == vals);
    printf("%lld %lld\n", a, b);
}
