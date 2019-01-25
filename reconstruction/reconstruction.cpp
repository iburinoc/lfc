// https://oi.edu.pl/en/archive/pa/2008/odb

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int main()
{
    int N;
    cin >> N;
    // Split into 6 * 5 / 2 regions, plus N for individuality
    vector<ll> P;
    P.push_back(2);
    ll R = min(N, 5);
    if (N == 7) {
        R = min(N, 6);
    }
    ll Rs = (N + R - 1) / R;
    vector<ll> O(N, 1);
    vector<vector<int>> Ri(R);
    for (int i = 0; i < N; i++) {
        Ri[i % R].push_back(i);
    }

    for (int p = 3; P.size() < (R * (R - 1) / 2 + N); p += 2) {
        bool good = true;
        for (auto q : P) {
            if (p % q == 0) {
                good = false;
                break;
            }
            if (q * q >= p) {
                break;
            }
        }
        if (good) {
            P.push_back(p);
        }
    }

    int pi = 0;
    for (int i = 0; i < R; i++) {
        for (int j = i + 1; j < R; j++) {
            for (auto k : Ri[i]) {
                O[k] *= P[pi];
            }
            for (auto k : Ri[j]) {
                O[k] *= P[pi];
            }
            pi++;
        }
    }
    for (int i = 0; i < R; i++) {
        for (int j = 1; j < Ri[i].size(); j++) {
            O[Ri[i][j]] *= P[pi++];
        }
    }
    for (int i = 0; i < N; i++) {
        cout << O[i] << endl;
    }
}
