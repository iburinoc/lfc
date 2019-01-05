#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vi> vvb;
typedef tuple<int,int,int> tiii;

int P, V, A;

vector<char> a0;
vi a1, a2;

vvi worlds;

void generate_worlds(int i, vi& cur) {
    if (i == V) {
        worlds.push_back(cur);
        return;
    }
    if (a0[i] == '=') {
        for (int v = a1[i]; v <= a2[i]; v++) {
            cur.push_back(v);
            generate_worlds(i+1, cur);
            cur.pop_back();
        }
        return;
    }
    int v1 = cur[a1[i]-1];
    int v2 = cur[a2[i]-1];
    int res;
    switch (a0[i]) {
        case '+': res = v1+v2; break;
        case '-': res = v1-v2; break;
        case '*': res = v1*v2; break;
        case '/': res = v1/v2; break;
        case '%': res = v1%v2; break;
        case '>': res = v1>v2; break;
        default: assert(0);
    }
    cur.push_back(res);
    generate_worlds(i+1);
    cur.pop_back();
}

int N;
vvi clas;
vvb answer;

int main() {
    cin >> P >> V >> A;
    a0.resize(V);
    a1.resize(V);
    a2.resize(V);
    for (int i = 0; i < V; i++) {
        cin >> a0[i] >> a1[i] >> a2[i];
    }

    generate_worlds(0, vi());
    N = worlds.size();
    clas = vvi(P, vi(N, 0));
    answer = vvb(A, vb(N, 0));
    unordered_set<int> S;
    for (int i = 0; i < N; i++) {
        S.insert(i);
    }

    unordered_set<int> to_bc;
    for (int i = 0; i < A; i++) {
        char c;
        int g, n;
        cin >> c >> g >> n;
        switch (c) {
        case 'S': {
            // Prince g learns the value of n, stratify classes by value of n
            vector<tiii> v;
            for (int w = 0; w < N; w++) {
                v.push_back(tiii(clas[g][w], worlds[w][n], w));
            }
            sort(v.begin(), v.end());
            int cl, val, id;
            tie(cl, val, id) = v[0];
            for (int j = 0; j < N; j++) {
                int ccl, cval, cid;
                tie(ccl, cval, cid) = v[j];
                if (ccl != cl || cval != val) {
                    // New class
                    cl = cid;
                    val = cval;
                }
                assert(cl <= cid);
                clas[g][cid] = cl;
            }
            break;
        }
        case 'T':
        case 'N':
        case 'X': {
            // Prince g says whether they know the value of n
            // Assign answers, insert into to_bc, and if T or N update sorceror
            // Create and remove elements from set as we go, the representative
            // is the minimum element of the class
            unordered_set<int> clids;
            for (int w = 0; w < N; w++) {
                if (clas[g][w] == w) {
                    clids.insert(w);
                }
                if (worlds[w][n] != worlds[clas[g][w]][n]) { // can't know the answer for this class
                    clids.erase(clas[g][w]);
                }
            }
            for (int w = 0; w < N; w++) {
                answer[i][w] = clids.count(clas[g][w]) > 0;
            }

            to_bc.insert(i);

            if (c != 'X') {
                bool val = c == 'N';
                for (int w = 0; w < N; w++) {
                    if (val == answer[i][w]) {
                        S.erase(w);
                    }
                }
            } else {
                    set<bool> ans;
                    for (auto w : S) {
                        ans.insert(answer[i][w]);
                    }
                    if (ans.size() == 2) {
                        cout << "NIE WIEM\n";
                    } else if (ans.count(false) > 0) {
                        cout << "NIE\n";
                    } else {
                        cout << "TAK\n";
                    }
            }
            break;
        }
        case 'A': {
            for (auto q : to_bc) {
                for (int p = 0; p < P; p++) {
                    // Prince p learns of the answer to question q for each q in to_bc
                    vector<tiii> v;
                    for (int w = 0; w < N; w++) {
                        v.push_back(tiii(clas[p][w], answer[q][w], w));
                    }
                    sort(v.begin(), v.end());
                    int cl, val, id;
                    tie(cl, val, id) = v[0];
                    for (int j = 0; j < N; j++) {
                        int ccl, cval, cid;
                        tie(ccl, cval, cid) = v[j];
                        if (ccl != cl || cval != val) {
                            // New class
                            cl = cid;
                            val = cval;
                        }
                        assert(cl <= cid);
                        clas[p][cid] = cl;
                    }
                }
            }
            to_bc.erase(to_bc.begin(), to_bc.end());
            break;
        }
        case 'M': {
            for (auto w : S) {
                if (worlds[w][n] != g) {
                    S.erase(w)
                }
            }
            break;
        }
        case 'Q': {
            set<int> answers;
            for (auto w : S) {
                answers.insert(worlds[w][n]);
            }
            bool first = true;
            for (auto v : answers) {
                if (!first) {
                    cout << " ";
                }
                first = false;
                cout << v;
            }
            cout << endl;
            break;
        }
        }
    }
}
