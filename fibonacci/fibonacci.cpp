// http://oi.edu.pl/en/archive/oi/12/sum

#include <bits/stdc++.h>
using namespace std;

inline void rep(string& S, int i, const string& r)
{
    for (int j = 0; j < r.size(); j++) {
        S[j + i] = r[j];
    }
}

int main()
{
    auto start = clock();
    int N, M;
    scanf("%d", &N);
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    scanf("%d", &M);
    A.resize(max(N, M));
    for (int i = 0; i < M; i++) {
        int v;
        scanf("%d", &v);
        A[i] += v;
    }

    N = max(N, M);
    assert(A[N - 1] >= 1);
    for (int i = 0; i < 4; i++) {
        A.push_back(0);
    }
    string S(A.size(), '0');
    for (int i = 0; i < A.size(); i++) {
        S[i] += A[i];
    }
#ifdef IB_DEBUG
    cout << S << endl;
#endif

    for (int i = N - 1; i >= 0; i--) {
        const string s4 = S.substr(i, 4);
        if (s4 == "0020") {
            rep(S, i, "1001");
        } else if (s4 == "1020") {
            rep(S, i, "2001");
        }
        const string s3 = S.substr(i, 3);
        if (s3 == "210") {
            rep(S, i, "101");
        } else if (i == 0) {
            if (s3 == "020") {
                rep(S, i, "101");
            } else if (S[0] == '2') {
                rep(S, i, "01");
            }
        }
    }
#ifdef IB_DEBUG
    cout << S << endl;
#endif
    for (int i = 0; i < N; i++) {
        if (S.substr(i, 3) == "120") {
            rep(S, i, "011");
        }
    }

    for (int i = 0; i < N; i++) {
        if (S[i] == '0') {
            continue;
        }
        int j = i;
        for (; S[j] == '1'; j++)
            ;
        int k = j;
        for (; j > i + 1; j -= 2) {
            S[j] = '1';
            S[j - 1] = '0';
            S[j - 2] = '0';
        }
        i = k - 1;
    }
    int l = 0;
    for (int i = S.size(); i >= 0; i--) {
        if (S[i] == '1') {
            l = i + 1;
            break;
        }
    }

    printf("%d", l);
    for (int i = 0; i < l; i++) {
        printf(" %c", S[i]);
    }
    printf("\n");
}
