#include "../../AOC.h"

vector<long> v;
long tgt;

bool possible(long last, int i, int n) {
    if(i == n) {
        return last == tgt;
    }

    bool a = possible(last * v[i], i + 1, n);
    bool b = possible(last + v[i], i + 1, n);
    
    long esp = 1;
    long t = v[i];
    while(t) {
        t /= 10L;
        esp *= 10;
    }

    bool c = possible(last*esp + v[i], i + 1, n);

    return a || b || c;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    long ans = 0;
    while(getline(cin, buf)) {
        if(buf.empty())
            continue;

        stringstream ss;
        ss << buf;
        ss >> tgt;
        ss.ignore();

        long a;
        v.clear();
        while(ss >> a) {
            v.push_back(a);
        }

        if(possible(v[0], 1, v.size())) {
            ans += tgt;
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}