#include <bits/stdc++.h>
#include <string>
using namespace std;
 
//ANOTHER BRUTE FORCE, BUT IT KEEPS WORKING

vector<long> v;
long tgt;

bool possible(long last, int i, int n) {
    if(i == n) {
        return last == tgt;
    }

    bool a = possible(last * v[i], i + 1, n);
    bool b = possible(last + v[i], i + 1, n);
    bool c = possible(stol( to_string(last) + to_string(v[i]) ), i + 1, n);

    return a || b || c;
}

int main(int argc, char const *argv[]) {
    string buf;
    long ans = 0;
    while(getline(cin, buf)) {
        if(buf.empty())
            continue;

        stringstream ss;
        ss << buf;
        ss >> tgt;
        ss.ignore();

        long a;
        v.clear();
        while(ss >> a) {
            v.push_back(a);
        }

        if(possible(v[0], 1, v.size())) {
            ans += tgt;
        }
    }

    cout << ans << endl;

    return 0;
}