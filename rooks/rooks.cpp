// http://oi.edu.pl/en/archive/oi/3/wie

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef tuple<int, int, int> piii;

vector<int> solve(vector<piii> A)
{
    int N = A.size();
    sort(A.begin(), A.end());

    set<pii> RE;
    vector<int> R(N);
    for (int i = 0, ai = 0; i < N; i++) {
        while (ai < N) {
            int x, y, idx;
            tie(x, y, idx) = A[ai];
            if (x > i)
                break;
            RE.insert(pii(y, idx));
            ai++;
        }
        int y, idx;
        tie(y, idx) = *RE.begin();
        if (y <= i)
            return vector<int>();
        RE.erase(RE.begin());
        R[idx] = i;
    }
    return R;
}

int main()
{
    int N;
    cin >> N;

    vector<piii> A1(N), A2(N);
    for (int i = 0; i < N; i++) {
        int l1, l2, r1, r2;
        cin >> l1 >> l2 >> r1 >> r2;
        l1--;
        l2--;
        A1[i] = piii(l1, r1, i);
        A2[i] = piii(l2, r2, i);
    }

    vector<int> R = solve(A1);
    vector<int> C = solve(A2);
    if (R.size() == 0 || C.size() == 0) {
        cout << "NIE\n";
        return 0;
    }
    for (int i = 0; i < N; i++) {
        cout << (R[i] + 1) << " " << (C[i] + 1) << endl;
    }
}
