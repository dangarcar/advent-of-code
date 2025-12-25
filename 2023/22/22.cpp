#include "../../AOC.h"

struct Brick {
    int x1,y1,z1;
    int x2,y2,z2;
};

bool isOver(const Brick& a, const Brick& b) {
    if (a.x1 > b.x2 || b.x1 > a.x2)
        return false;

    if (a.y2 < b.y1 || b.y2 < a.y1)
        return false;

    return a.z1-1 == b.z2;
}

signed main() {
    AoCTimer timer;
    
    vector<Brick> bricks;
    string str;
    while(getline(cin, str)) {
        if(str.empty()) continue;

        istringstream iss(str);
        Brick b; char c;
        iss >> b.x1 >> c >> b.y1 >> c >> b.z1;
        iss.ignore();
        iss >> b.x2 >> c >> b.y2 >> c >> b.z2;

        bricks.push_back(b);
    }

    auto n = bricks.size();
    sort(bricks.begin(), bricks.end(), [](auto& a, auto& b){
        return a.z1 < b.z1;
    });

    vector<vector<int>> child(n), parent(n);
    for(int i=0; i<n; ++i) {
        for(;;) {
            bool over = bricks[i].z1 == 1;
            for(int j=0; j<i; ++j) {
                if(isOver(bricks[i], bricks[j])) {
                    over = true;
                    parent[i].push_back(j);
                    child[j].push_back(i);
                }
            }

            if(over) break;
            
            bricks[i].z1--;
            bricks[i].z2--;
        }
    }

    int ans = 0;
    for(int i=0; i<n; ++i) {
        vector<bool> falling(n, false);
        queue<int> q;
        falling[i] = true;
        q.push(i);

        int fallen = 0;

        while(!q.empty()) {
            auto u = q.front();
            q.pop();

            for(auto v: child[u]) {
                if(falling[v])
                    continue;

                bool stable = false;
                for(auto w: parent[v])
                    if(!falling[w])
                        stable = true;

                if(!stable) {
                    fallen++;
                    falling[v] = true;
                    q.push(v);
                }
            }
        }

        //cout << i << ' ' << fallen << '\n';
        ans += fallen;
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}
