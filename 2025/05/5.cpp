#include "../../AOC.h"




signed main() {
    AoCTimer timer;

    string buf;
    vector<pair<int, int>> v;
    while(getline(cin, buf), !buf.empty()) {
        istringstream iss(buf);
        int a, b;
        char ch;
        iss >> a >> ch >> b;

        v.push_back({a, -1});
        v.push_back({b, 1});
    }

    sort(v.begin(), v.end());

    int ans = 0, par = 0, src = 0;
    for(auto [a, p]: v) {
        if(par == 0)
            src = a;
        
        par += p;

        if(par == 0)
            ans += a - src + 1;
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}