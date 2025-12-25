#include "../../AOC.h"

#define SCALE 1000000

vector<pair<int,int>> pos;
vector<bool> iEmpty, jEmpty;

long distance(int u, int v) {    
    auto [i1, j1] = pos[u];
    auto [i2, j2] = pos[v];

    if(i1 > i2) swap(i1, i2);
    if(j1 > j2) swap(j1, j2);
    
    long idst=0, jdst=0;
    for(int i=i1; i<i2; i++) {
        if(iEmpty[i])
            idst += SCALE;
        else
            idst++;
    }

    for(int j=j1; j<j2; ++j) {
        if(jEmpty[j])
            jdst += SCALE;
        else
            jdst++;
    }

    return idst + jdst;
}

signed main() {
    AoCTimer timer;
    
    vector<string> board;
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) 
            continue;
        
        board.push_back(buf);
    }

    int n = board.size();
    iEmpty.assign(n, true);
    jEmpty.assign(n, true);
    
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(board[i][j] == '#') {
                pos.push_back({i, j});
                iEmpty[i] = false;
                jEmpty[j] = false;
            }
        }
    }

    long ans = 0;
    for(int i=0; i<pos.size(); ++i)
        for(int j=0; j<i; ++j)
            ans += distance(i, j);

    cout << "Part 2 answer: " << ans << endl;

    return 0;
} 