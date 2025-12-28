#include "../../AOC.h"

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    map<string, set<string>> adj;
    string buf;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;

        string u(buf.begin(), buf.begin()+2), v(buf.begin()+3, buf.begin()+5);
        adj[u].insert(v);
        adj[v].insert(u);
    }

    set<string> ans;
    for(auto [u, ad]: adj) {
        set<string> s;
        s.insert(u);

        for(auto v: adj[u]) {
            bool group = true;            
            for(auto w: s)
                if(adj[v].count(w) == 0)
                    group = false;

            if(group)
                s.insert(v);
        }

        if(ans.size() < s.size())
            ans = s;
    }

    buf.clear();
    for(auto e: ans) 
        buf += e + ",";
    buf.resize(buf.size()-1);

    cout << "Part 2 answer: " << buf << endl;

    return 0;
}