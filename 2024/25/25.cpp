#include <bits/stdc++.h>
using namespace std;

bool compatible(const vector<int>& a, const vector<int>& b) {
    int k = 6;
    
    for(int i=0; i<a.size(); ++i) {
        if(a[i] + b[i] > k)
            return false; 
    }

    return true;
}

int main(int argc, char const *argv[]) {
    string buf;
    vector<vector<int>> keys, locks;
    vector<string> s;
    while(getline(cin, buf)) {
        if(buf.empty()) {
            if(s.empty()) 
                continue;

            vector<int> h(s[0].size(), -1);
            for(auto& v: s) {
                for(int i=0; i<v.size(); ++i)
                    h[i] += v[i] == '#';
            }

            if(s[0][0] == '#')
                keys.push_back(h);
            else
                locks.push_back(h);
                
            s.clear();
        } else {
            s.push_back(buf);
        }
    }


    int ans = 0;

    for(auto& k: keys) {
        for(auto& l: locks) {
            for(auto e: k) cout << e << ' ';
            cout << "-> ";
            for(auto e: l) cout << e << ' ';

            bool comp = true;
            for(int i=0; i<5; ++i) {
                if(k[i] + l[i] > 5) {
                    comp = false;
                    break;
                }
            }

            cout << "- " << comp << endl;
            ans += comp;
        }
    }

    cout << ans << endl;

    return 0;
}