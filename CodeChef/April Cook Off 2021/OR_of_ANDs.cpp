
//------------------------------------------------------------------------------
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>
// #include <cmath>
// #include <algorithm>
// #include <unordered_map>
// #include <map>
// #include <set>
// #include <unordered_set>
//------------------------------------------------------------------------------
using namespace std;
//------------------------------------------------------------------------------
#define FastIO ios_base::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define v(Type) vector<Type>
#define w(T)  \
    int T;    \
    cin >> T; \
    while (T--)
#define int long long int
#define mod 1000000007ll
#define endl "\n"
//------------------------------------------------------------------------------
// Any fucntion can be called using Math.function_name();
//------------------------------------------------------------------------------
class Math
{
public:
    //Returns gcd of two numbers
    int gcd(int a, int b)
    {
        return (a % b == 0) ? b : gcd(b, a % b);
    }

    //Returns lcm of two numbers
    int lcm(int a, int b)
    {
        return a * (b / gcd(a, b));
    }

    // Returns flag array isPrime
    // isPrime[i] = true (if i is Prime)
    // isPrime[i] = false (if i is not Prime)
    vector<bool> *seiveOfEratosthenes(const int N)
    {
        vector<bool> *isPrime = new vector<bool>(N + 1, true);
        (*isPrime)[0] = (*isPrime)[1] = false;
        for (int i = 2; i * i <= N; ++i)
            if ((*isPrime)[i])
                for (int j = i * i; j <= N; j += i)
                    (*isPrime)[j] = false;

        return isPrime;
    }

    //Returns (x ^ n)
    int pow(const int &x, int n)
    {
        if (n == 0)
            return 1;
        int h = pow(x, n / 2);
        return (n & 1) ? h * h * x : h * h;
    }

    //Returns (x ^ n) % M
    int pow(const int &x, int n, const int &M)
    {
        if (n == 0)
            return 1;
        int h = pow(x, n / 2) % M;
        return (n & 1) ? (h * h * x) % M : (h * h) % M;
    }

    //Returns all Primes <= N
    vector<int> *primesUptoN(const int N)
    {
        vector<bool> *isPrime = seiveOfEratosthenes(N);
        vector<int> *Primes = new vector<int>;
        if (2 <= N)
            (*Primes).push_back(2);
        for (int i = 3; i <= N; i += 2)
            if ((*isPrime)[i])
                (*Primes).push_back(i);
        return Primes;
    }

} Math;
//------------------------------------------------------------------------------

struct item
{
    //
    int v;
};

class SegmentTree
{
private:
    v(item) tree;
    int size;
    item neutralValue;

    item merge(item &a, item &b)
    {
        //
        return {a.v | b.v};
    }

    item single(int val)
    {
        //
        return {val};
    }

    void init(v(int) & A)
    {
        size = 1;
        while (size < (int)A.size())
            size <<= 1;
        tree.resize(size << 1);
        build(A, 0, 0, size);
    }

    void build(v(int) & A, int x, int lx, int rx)
    {

        if (rx - lx == 1)
        {
            if (lx < (int)A.size())
                tree[x] = single(A[lx]);

            return;
        }

        int mx = (lx + rx) >> 1;

        build(A, (x << 1) + 1, lx, mx);
        build(A, (x << 1) + 2, mx, rx);

        tree[x] = merge(tree[(x << 1) + 1], tree[(x << 1) + 2]);
    }

    void update(int &idx, int &val, int x, int lx, int rx)
    {

        if (rx - lx == 1)
        {
            tree[x] = single(val);
            return;
        }

        int mx = (lx + rx) >> 1ll;

        if (idx < mx)
            update(idx, val, (x << 1) + 1, lx, mx);
        else
            update(idx, val, (x << 1) + 2, mx, rx);

        tree[x] = merge(tree[(x << 1) + 1], tree[(x << 1) + 2]);
    }

    item query(int x, int lx, int rx)
    {
        return tree[x];
    }

public:
    SegmentTree(v(int) & A)
    {
        init(A);
        return;
    }

    void update(int &idx, int &val)
    {
        update(idx, val, 0, 0, size);
        return;
    }

    item query()
    {
        return query(0, 0, size);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    v(int) A(n);
    for (int i = 0; i < n; i++)
        cin >> A[i];

    SegmentTree st(A);
    auto ans = st.query();
    cout << ans.v << endl;
    while (q--)
    {
        int i, v;
        cin >> i >> v;
        i--;
        st.update(i, v);
        auto ans = st.query();
        cout << ans.v << endl;
    }
}
//------------------------------------------------------------------------------
int32_t main()
{
    FastIO;

    w(T)
        solve();

    return 0;
}
//------------------------------------------------------------------------------
