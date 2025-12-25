#include "../../AOC.h"

signed main() {
    AoCTimer timer;
    
    string s;
    vector<int> v, w;
    unordered_map<int, pair<int, int>> m;
    while(getline(cin, s)) {
        stringstream ss;
        ss << s;
        int a, b;
        ss >> a >> b;
        v.push_back(a);
        w.push_back(b);

        m[a].first++;
        m[b].second++;
    }

    int n = v.size();

    sort(v.begin(), v.end());
    sort(w.begin(), w.end());

    int ans1 = 0;
    for(int i=0; i<n; ++i) {
        ans1 += abs(v[i] - w[i]);
    }

    cout << "Part 1 answer: " << ans1 << endl;

    int ans2 = 0;
    for(auto [k, v]: m) {
        auto [a, b] = v;
        ans2 += k*a*b;
    }

    cout << "Part 2 answer: " << ans2 << endl;

    return 0;
}