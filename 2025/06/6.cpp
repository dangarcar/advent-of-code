#include "../../AOC.h"

#define int long long


signed main() {
    AoCTimer timer;

    string buf;
    vector<string> in;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;
        in.push_back(buf);
    }
    
    vector<string> trans(in[0].size());
    for(int j=0; j<in[0].size(); ++j) {
        for(int i=0; i<in.size(); ++i)
            trans[j].push_back(in[i][j]);
    }

    int ans = 0;
    for(int i=0; i<trans.size(); ++i) {
        istringstream iss(trans[i]);
        int a; char c;
        iss >> a >> c;

        while(++i < trans.size() && trans[i].find_first_not_of(' ') != string::npos) {
            if(c == '*')
                a *= stol(trans[i]);
            else if(c == '+')
                a += stol(trans[i]);
            else exit(1);
        }

        ans += a;
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}