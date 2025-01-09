#include <bits/stdc++.h>
using namespace std;

struct ufds {
    int numSets;
    vector<int> p;

    ufds(int n): numSets(n), p(n, -1) {}

    int find(int i) {
        return (p[i] < 0)? i : p[i] = find(p[i]);
    }

    bool related(int i, int j) {
        return find(i) == find(j);
    }

    void join(int i, int j) {
        int x = find(i), y = find(j);
        if(x == y) return;
        if(p[x] < p[y]) swap(x, y);
        p[y] += p[x];
        p[x] = y;
        --numSets;
    }

    int size(int i) {
        return -p[find(i)];
    }
};

int main(int argc, char const *argv[]) {
    string str;
    map<string, int> alias;
    vector<pair<int,int>> edges;
    int n = 0;
    while(getline(cin, str)) {
        if(str.empty()) continue;
        istringstream iss(str);

        string name, conn; 
        iss >> name;
        name = name.substr(0, 3);
        if(!alias.contains(name))
            alias[name] = n++;
        
        while(iss >> conn) {
            if(!alias.contains(conn))
                alias[conn] = n++;

            edges.push_back({alias[name], alias[conn]});
        }
    }

    while(true) {
        ufds uf(n);
        auto es = edges;
        
        while(uf.numSets > 2) {
            int j = rand()%es.size();
            auto [u, v] = es[j];
            uf.join(u, v);
            es.erase(es.begin() + j);
        }
        
        int ans = 1;
        for(int i=0; i<n; ++i) {
            if(uf.p[i] < 0) {
                ans *= -uf.p[i];

                if(uf.p[i] > -5) { //Remove small groups
                    ans = 0;
                    break;
                }
            }
        }
        
        if(ans != 0) {
            cout << "Answer: " << ans << '\n';
            break;
        }
    }

    return 0;
}