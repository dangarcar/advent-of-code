#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> adj;
vector<bool> visited, reachable;
unordered_map<string, int> idx;


int dfs(int u, int dst) {
    if(u == dst)
        return 1;

    int a = 0;
    for(int v: adj[u]) {
        if(reachable[v])
            a += dfs(v, dst);
    }

    return a;
}

bool order(int u, int dst) {
    if(visited[u])
        return false;
    visited[u] = true;

    if(u == dst)
        return true;

    bool a = false;
    for(auto v: adj[u]) {
        a |= order(v, dst);
    }

    return a;
}

bool reach(int u, int dst) {
    if(visited[u])
        return reachable[u];
    visited[u] = true;
    
    if(u == dst)
        return reachable[u] = true;    

    bool a = false;
    for(auto v: adj[u]) {
        a |= reach(v, dst); 
    }

    return reachable[u] = a;
}


signed main() {
    string buf;
    int id = 0;

    while(getline(cin, buf)) {
        istringstream iss(buf);
        iss >> buf;

        string a(buf.begin(), buf.end()-1);

        if(!idx.contains(a)) {
            idx[a] = id;
            adj.push_back({});
            id++;
        }

        int u = idx[a];
        while(iss >> buf) {
            if(!idx.contains(buf)) {
                idx[buf] = id;
                adj.push_back({});
                id++;
            }

            int v = idx[buf];

            adj[u].push_back(v);
        }
    }

    int n = adj.size();
    int scheme[4] = {idx["svr"], idx["fft"], idx["dac"], idx["out"]};

    visited.assign(n, 0);
    if(order(scheme[1], scheme[2]) == false)
        swap(scheme[1], scheme[2]);


    reachable.assign(n, 0);
    for(int i=1; i<4; ++i) {
        visited.assign(n, 0);
        reach(scheme[i-1], scheme[i]);
    }

    int ans = 1;
    for(int i=1; i<4; ++i) {
        ans *= dfs(scheme[i-1], scheme[i]);
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}