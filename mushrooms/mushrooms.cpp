// https://oi.edu.pl/en/archive/pa/2010/grz

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

int main()
{
    ll N, T;
    scanf("%lld %lld", &N, &T);
    ll best = 0;
    ll sum = 0;
    ll prev = 0;
    for (ll i = 0; i < N && i <= T; i++) {
        ll a;
        scanf("%lld", &a);
        ll tr = (T - i);
        sum += a;
        best = max(best, a * (tr / 2) + sum);
        if (i > 0) {
            best = max(best, sum + prev * ((tr + 1) / 2) + a * (tr / 2));
        }
        prev = a;
    }
    cout << best << endl;
}
