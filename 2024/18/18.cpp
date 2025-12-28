#include "../../AOC.h"

int incX[] = {0, 0, 1, -1};
int incY[] = {1, -1, 0, 0};

int path(const set<pair<int,int>>& bytes, int n) {
    vector<vector<int>> dist(n, vector<int>(n, -1));
    queue<pair<int,int>> q;
    dist[0][0] = 0;
    q.push({0, 0});

    while(!q.empty()) {
        auto [y, x] = q.front();
        q.pop();

        for(int k=0; k<4; ++k) {
            int nx = x + incX[k], ny = y + incY[k];

            if(0 <= nx && nx < n
            && 0 <= ny && ny < n
            && bytes.count({y, x}) == 0
            && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({ny, nx});
            }
        }
    }

    return dist[n-1][n-1];
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    int n = 71;
    vector<pair<int,int>> bytes;
    
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty())
            continue;

        stringstream ss;
        ss << buf;
        int x, y;
        ss >> x;
        ss.ignore();
        ss >> y;

        bytes.push_back({y, x});
    }


    int l=0, r=bytes.size()-1;
    while(l+1 < r) {
        int m = (l+r) / 2;

        set<pair<int,int>> s(bytes.begin(), bytes.begin() + m+1);
        
        if(path(s, n) != -1)
            l = m;
        else
            r = m;
    }

    cout << "Part 2 answer: " << bytes[r].second << ',' << bytes[r].first << endl;

    return 0;
}