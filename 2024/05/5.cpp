#include <bits/stdc++.h>
using namespace std;

set<int> adj[100];

bool isVectorOrdered(vector<int>& v) {
    bool ord = true;
    
    for(int i=0; i<v.size(); ++i) {
        for(int j=i; j>=0; --j) {
            if(adj[v[i]].count(v[j]))
                ord = false;
        }
    }

    return ord;
}

void orderVector(vector<int>& v) {
    for(int i=0; i<v.size(); ++i) {
        for(int j=0; j<i; ++j) {
            if(adj[v[i]].count(v[j]))
                swap(v[i], v[j]);
        }
    }
}

int main(int argc, char const *argv[]) {
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) break;

        stringstream ss(buf);
        int a, b;
        char c;
        ss >> a >> c >> b;

        adj[a].insert(b);
    }

    int ans = 0;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;

        stringstream ss(buf);
        vector<int> v;
        int a;
        while(ss >> a) {
            ss.ignore();
            v.push_back(a);
        }

        if(!isVectorOrdered(v)) {
            orderVector(v);
            assert(isVectorOrdered(v));

            ans += v[v.size()/2];
        }
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}