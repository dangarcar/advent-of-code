#include <bits/stdc++.h>
using namespace std;

vector<string> prefs;
unordered_map<string, long> cache;

long solve(const string& s) {
    if(s.empty())
        return 1;
    if(cache.count(s))
        return cache.at(s);

    long ret = 0;
    for(auto& p: prefs) {
        if(s.size() >= p.size() && strncmp(s.c_str(), p.c_str(), p.size()) == 0) {
            string ns(s.begin() + p.size(), s.end());
            ret += solve(ns);
        }
    }

    cache.insert({s, ret});
    return ret;
}

int main(int argc, char const *argv[]) {
    string buf;
    getline(cin, buf);
    stringstream ss;
    ss << buf;
    while(getline(ss, buf, ',')) {
        buf.erase(remove(buf.begin(), buf.end(), ' '), buf.end());
        if(!buf.empty())
            prefs.push_back(buf);
    }

    vector<string> tests;
    while(getline(cin, buf)) {
        if(buf.empty()) 
            continue;;
        tests.push_back(buf);
    }

    long ans = 0;
    for(auto& s: tests) {
        //cout << s << ' ' << solve(s) << endl;

        ans += solve(s);
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}