// http://oi.edu.pl/en/archive/oi/2/kod

#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct BlockedArray {
    vector<vi> data;

    BlockedArray(int n)
    {
        vi v;
        for (int c = 0; c < n; c++) {
            v.push_back(c);
            if (v.size() * v.size() >= n) {
                data.push_back(v);
                v.clear();
            }
        }
        if (!v.empty()) {
            data.push_back(v);
        }
    }

    int getAndDelete(int ith)
    {
        assert(data.size() > 0);
        int i = 0;
        while (ith >= data[i].size()) {
            ith -= data[i].size();
            i++;
        }
        int val = data[i][ith];
        data[i].erase(data[i].begin() + ith);
        return val;
    }
};

void nie()
{
    cout << "NIE\n";
    exit(0);
}

int main()
{
    int N;
    cin >> N;
    vector<int> B(N);
    for (int i = 0; i < N; i++) {
        cin >> B[i];
    }

    BlockedArray ba(N);
    vector<int> A(N);
    for (int i = N - 1; i >= 0; i--) {
        if (B[i] > i)
            nie();

        int ith = i - B[i];
        A[i] = ba.getAndDelete(ith) + 1;
    }
    for (auto v : A) {
        cout << v << endl;
    }
}
