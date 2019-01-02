// https://www.acmicpc.net/problem/8530
// On alternate judge because this problem isn't on szkopul yet

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;
const int MOD = 666;

short DPP[MAXN][MAXN][MOD][3];
short DPQ[MAXN][MAXN][MOD][3];

vector<int> S;

vector<vector<int>> div10(MOD);

short Q(int a, int b, int d, int i);
short P(int a, int b, int d, int i)
{
    if (a > b)
        return 0;
    short& res = DPP[a][b][d][i];
    if (res != -1) {
        return res;
    }
    return res = P(a + 1, b, d, i) + Q(a, b, d, i);
}

short IMUL[] = { 11, 101, 335 };

short Q(int a, int b, int d, int i)
{
    if (a > b)
        return 0;
    if (d > MOD)
        return 0;
    if (i >= 3)
        return 0;
    short& res = DPQ[a][b][d][i];
    if (res != -1) {
        return res;
    }

    res = 0;
    if (a == b) {
        // Length 1 polygon with modulo S[a]
        res = (S[a] == d) && (i == 1);
    } else {
        // Add inner palindromes
        res = Q(a, b - 1, d, i);
        if (S[a] == S[b]) { // palindromic
            // any sub-palindromes must have length (i-2) % 3
            // this will contribute to the modulo a sum of (10^(i+1))*S[a]
            // the sub-palindrome will contribute 10*td
            // need 10*td == d' = d - (10^(i+1))*S[a]
            int ti = (i + 1) % 3;
            int dprime = (d - ((IMUL[ti] * S[a]) % MOD) + MOD) % MOD;
            if (ti == 0 && dprime == 0) {
                // We can use these two as a an answer on their own
                res++;
            }
            for (auto td : div10[dprime]) {
                res += P(a + 1, b - 1, td, ti);
            }
            res %= MOD;
        }
    }
    return res;
}

int main()
{
    memset(DPP, -1, sizeof(DPP));
    memset(DPQ, -1, sizeof(DPQ));
    for (int i = 0; i < MOD; i++) {
        div10[(i * 10) % MOD].push_back(i);
    }
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        S.push_back(s[i] - '0');
    }
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        ans += P(0, s.size() - 1, 0, i);
    }
    ans %= MOD;
    if (ans == 0)
        ans = MOD;
    cout << ans << endl;
}
