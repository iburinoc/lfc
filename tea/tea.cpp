// https://oi.edu.pl/en/archive/amppz/2011/her

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    if (n == 1) {
        cout << "HM\n";
        return 0;
    }
    int ch = 0, cm = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == 'H')
            ch++;
        else
            cm++;
    }
    if (ch > cm) {
        cout << "H\n";
    } else if (cm > ch) {
        cout << "M\n";
    } else {
        cout << "HM"[s[n - 2] == 'H'] << endl;
    }
}
