// https://oi.edu.pl/en/archive/oi/13/ork
// Notes: Didn't have enough memory to duplicate array,
// hence the transposer wrapper

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;

ll K, M, N;

template <typename T>
struct TransposerRow {
    TransposerRow(vector<vector<T>>* V, size_t R)
        : V(V)
        , R(R)
    {
    }

    const T& operator[](size_t C) const
    {
        return (*V)[C][R];
    }

    size_t size() const
    {
        return V->size();
    }

    vector<vector<T>>* V;
    size_t R;
};

template <typename T>
struct Transposer {
    Transposer(vector<vector<T>>* V)
        : V(V)
    {
    }

    TransposerRow<T> operator[](size_t R) const
    {
        return TransposerRow<T>(V, R);
    }

    size_t size() const
    {
        return (*V)[0].size();
    }

    vector<vector<T>>* V;
};

template <typename T>
ll boxSum(ll l, ll r, ll t, ll b, T& S)
{
    return S[b + 1][r + 1] - S[b + 1][l] - S[t][r + 1] + S[t][l];
}

template <typename Vec0, typename Vec1>
int solve(ll a, const Vec1& F, const Vec0& S)
{
    // assume we'll take all the columns away
    ll ans = 0;
    ll L = 0;
    ll R = F[0].size() - 1;
    ll T = 0;
    ll B = F.size() - 1;
    while (L <= R) {
        if (T > B)
            return INT_MAX;
        if (boxSum(L, L, T, B, S) <= K) {
            L++;
        } else if (boxSum(R, R, T, B, S) <= K) {
            R--;
        } else if (T < a && boxSum(L, R, T, T, S) <= K) {
            T++;
            ans++;
        } else if (boxSum(L, R, B, B, S) <= K) {
            B--;
            ans++;
        } else {
            return INT_MAX;
        }
    }
    return F[0].size() + ans;
}

int main()
{
    scanf("%lld %lld %lld", &K, &M, &N);
    vector<vector<int>> F(N, vector<int>(M));
    for (ll r = 0; r < N; r++) {
        for (ll c = 0; c < M; c++) {
            scanf("%d", &F[r][c]);
        }
    }

    vvll S(N + 1, vll(M + 1, 0));
    for (ll r = 0; r < N; r++) {
        for (ll c = 0; c < M; c++) {
            S[r + 1][c + 1] = S[r + 1][c] + F[r][c];
        }
    }
    for (ll c = 0; c <= M; c++) {
        for (ll r = 0; r < N; r++) {
            S[r + 1][c] += S[r][c];
        }
    }

    int ans = INT_MAX;
    for (int a = 0; a < N; a++) {
        ans = min(ans, solve(a, F, S));
    }
    for (int a = 0; a < M; a++) {
        ans = min(ans, solve(a, Transposer<int>(&F), Transposer<ll>(&S)));
    }
    printf("%d\n", ans);
}
