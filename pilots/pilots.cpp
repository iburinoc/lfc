// https://oi.edu.pl/en/archive/oi/17/pil
//
// Notes:
//  - had to use uint32_t instead of ll for memory limit
//  - had to use scanf to fit in time limit

#include <bits/stdc++.h>

using namespace std;

typedef long long int ll;

struct MaxStack {
    stack<uint32_t> s, m;
    uint32_t top()
    {
        return s.top();
    }

    uint32_t max()
    {
        if (m.empty())
            return 0;
        return m.top();
    }

    void push(uint32_t a)
    {
        s.push(a);
        m.push(std::max(m.empty() ? a : m.top(), a));
    }

    void pop()
    {
        s.pop();
        m.pop();
    }

    bool empty()
    {
        return s.empty();
    }
    size_t size()
    {
        return s.size();
    }
};

struct MaxQueue {
    MaxStack s1, s2;
    uint32_t front()
    {
        return s2.top();
    }

    uint32_t max()
    {
        return std::max(s1.max(), s2.max());
    }

    void push(uint32_t a)
    {
        s1.push(a);
    }

    void pop()
    {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }

    bool empty()
    {
        return s1.empty() && s2.empty();
    }

    size_t size()
    {
        return s1.size() + s2.size();
    }
};

int main()
{
    uint32_t T, N;
    scanf("%u %u", &T, &N);

    MaxQueue maxq, minq;
    size_t best = 0;
    for (int i = 0; i < N; i++) {
        uint32_t v;
        scanf("%u", &v);
        maxq.push(v);
        minq.push(-v);

        while ((maxq.max() > v + T) || (-minq.max() + T < v)) {
            maxq.pop();
            minq.pop();
        }
        best = max(best, maxq.size());
    }
    cout << best << endl;
}
