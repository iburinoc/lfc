// https://oi.edu.pl/en/archive/ontak/2008/leo

#include <bits/stdc++.h>

using namespace std;

typedef uint64_t ull;
typedef vector<ull> vu;

const ull MOD = 1000000000;

struct Matrix {
    vector<vu> data;
    Matrix(int n)
        : data(n, vu(n))
    {
    }

    vu& operator[](size_t i) { return data[i]; }
    const vu& operator[](size_t i) const { return data[i]; }

    Matrix operator*(const Matrix& o) const
    {
        assert(data.size() == o.data.size());
        ull N = data.size();
        Matrix res(N);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ull val = 0;
                for (int k = 0; k < N; k++) {
                    val += data[i][k] * o.data[k][j];
                    if ((k & 0xf) == 0)
                        val %= MOD;
                }
                res[i][j] = val % MOD;
            }
        }
        return res;
    }

    vu operator*(const vu& o)
    {
        assert(data.size() == o.size());
        ull N = data.size();
        vu res(N);
        for (int i = 0; i < N; i++) {
            res[i] = 0;
            for (int k = 0; k < N; k++) {
                res[i] = (res[i] + data[i][k] * o[k]) % MOD;
            }
        }
        return res;
    }
};

ull N, K;
ull pascal[20][20][20];
int idx[20][20];

void initPascal()
{
    pascal[0][0][0] = 1;
    for (int p = 0; p <= K; p++) {
        for (int q = 0; q <= p; q++) {
            for (int m = 0; m + q <= p; m++) {
                pascal[p + 1][m][q] += pascal[p][m][q];
                pascal[p + 1][m][q] %= MOD;
                pascal[p + 1][m + 1][q] += pascal[p][m][q];
                pascal[p + 1][m + 1][q] %= MOD;
                pascal[p + 1][m][q + 1] += pascal[p][m][q];
                pascal[p + 1][m][q + 1] %= MOD;
            }
        }
    }
}

int gi(int p, int q)
{
    return idx[p][q];
}

int initIdx()
{
    int i = 1;
    for (int p = 0; p <= K; p++) {
        for (int q = 0; p + q <= K; q++) {
            idx[p][q] = i++;
        }
    }
    return i;
}

int main()
{
    cin >> N >> K;
    if (N <= 1) {
        cout << (1 + N) << endl;
    }
    initPascal();
    int maxIdx = initIdx();
    Matrix A(maxIdx);
    A[0][0] = 1;
    A[0][gi(K, 0)] = 1;
    vu initial(maxIdx, 1);
    for (int p = 0; p <= K; p++) {
        for (int q = 0; p + q <= K; q++) {
            // L_{i+1}^p L_{i}^q
            // sum_{k,j} choose(p, (k, j, p-k-j)) L_i^{k+q}L_{i-1}^j
            for (int k = 0; k <= p; k++) {
                for (int j = 0; j + k <= p; j++) {
                    ull coeff = pascal[p][k][j];
                    ull e1 = k + q;
                    ull e2 = j;
                    A[gi(p, q)][gi(e1, e2)] = coeff;
                }
            }
        }
    }
#ifdef IB_DEBUG
    for (const auto& row : A.data) {
        for (const auto& v : row) {
            cout << v << " ";
        }
        cout << endl;
    }
#endif

    Matrix R(maxIdx);
    for (int i = 0; i < maxIdx; i++) {
        R[i][i] = 1;
    }
    while (N) {
        if (N & 1) {
            R = R * A;
        }
        A = A * A;
        N >>= 1;
    }

    vu v = R * initial;
    cout << setw(9) << setfill('0') << v[0] << endl;
}
