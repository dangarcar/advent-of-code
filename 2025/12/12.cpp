#include "../../AOC.h"

//WHY DOES THIS WORK?????

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);

    vector<vector<string>> bs;
    vector<int> areas;
    string buf;
    for(int i=0; i<6; ++i) {
        getline(cin, buf);
        bs.push_back({});
        getline(cin, buf);
        bs.back().push_back(buf);
        getline(cin, buf);
        bs.back().push_back(buf);
        getline(cin, buf);
        bs.back().push_back(buf);
        getline(cin, buf);
    }

    for(auto b: bs) {
        int a = 0;
        for(auto s: b)
            for(auto c: s) 
                a += c == '#';
        areas.push_back(a);
    }

    int ans = 0;
    while(getline(cin, buf)) {
        istringstream iss(buf);

        int w, h;
        char ch;
        iss >> w >> ch >> h >> ch;
        vector<int> v;
        for(int i=0; i<6; ++i) {
            int a; iss >> a;
            v.push_back(a); 
        }


        int area = w*h;

        int a = 0;
        for(int i=0; i<6; ++i) {
            a += v[i] *  areas[i];
        }

        if(a <= area)
            ans++;
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}