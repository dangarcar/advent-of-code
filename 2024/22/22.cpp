#include <bits/stdc++.h>
using namespace std;

#define SECRETS 2000

long op(long a) {
    a = (a xor (a * 64)) % 16777216;
    a = (a xor (a / 32)) % 16777216;
    a = (a xor (a * 2048)) % 16777216;

    return a;
}

vector<vector<int>> seq;
vector<vector<int>> diff;

struct key {
    int8_t a, b, c, d;

    key(int a, int b, int c, int d): a(a), b(b), c(c), d(d) {}
    auto operator<=>(const key&) const = default;
};

template<> struct std::hash<key> {
    size_t operator()(const key& k) const {
        return hash<long>()( *((long*)&k) );
    }
};

unordered_map<key, long> m;

int main(int argc, char const *argv[]) {
    int a;
    while(cin >> a) {
        vector<int> d(SECRETS), s(SECRETS + 1);
        s[0] = a;
        for(int i=0; i<SECRETS; ++i) {
            s[i+1] = op(s[i]);
            d[i] = (s[i+1]%10) - (s[i]%10);
        }

        seq.push_back(s);
        diff.push_back(d);
    }


    for(int i=0; i<seq.size(); ++i) {
        unordered_set<key> s;
        for(int j=4; j<=SECRETS; ++j) {
            key k( diff[i][j-4], diff[i][j-3], diff[i][j-2], diff[i][j-1] );
            if(s.count(k) == 0) {
                s.insert(k);
                m[k] += seq[i][j] % 10;
            }
        }
    }

    long ans = 0;
    for(auto [k, v]: m) {
        ans = max(ans, v);
    }
    cout << endl << ans << endl;

    return 0;
}