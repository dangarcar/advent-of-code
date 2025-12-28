#include "../../AOC.h"



struct Test {
    string goal;
    vector<vector<int>> moves;
    vector<int> reqs;
};  

int solve(const Test& t) {
    queue<pair<string, int>> q;
    q.push(make_pair(string(t.goal.size(), '.'), 0));

    while(!q.empty()) {
        auto [g, d] = q.front();
        q.pop();

        for(auto& m: t.moves) {
            auto s = g;
            for(auto i: m) {
                s[i] = (s[i]=='.')? '#':'.';
            }

            if(s == t.goal)
                return d + 1;

            q.push({s, d+1});
        }
    }


    return -1;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;    
    vector<Test> tests;
    while(getline(cin, buf)) {
        istringstream iss(buf);
        string s;
        iss >> s;
        Test t;
        t.goal = {s.begin()+1, s.end()-1};

        while(iss >> s, s[0] != '{'){
            vector<int> v;
            for(int i=1; i<s.size(); i+=2)
                v.push_back(s[i] - '0');
            t.moves.push_back(v);
        }

        iss = istringstream(string(s.begin()+1, s.end()-1));
        char ch;
        int a;
        while(iss >> a) {
            t.reqs.push_back(a);
            iss >> ch;
        }

        tests.push_back(t);
    }

    int ans = 0;
    for(auto& t: tests) {
        int a = solve(t);
        if(a == -1) exit(1);
        ans += a;
    }

    cout << "Part 1 answer: " << ans << '\n';

    return 0;
}