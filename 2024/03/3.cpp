#include <bits/stdc++.h>
#include <cstring>
#include <sstream>
#include <string>
using namespace std;

long multiply(const std::string& str) {
    stringstream ss;
    ss << str;
    long a, b;
    char c;
    ss >> a >> c >> b;
    
    string t;
    if(ss >> t)
        return 0;

    if(c == ',')
        return a * b;
    else
        return 0;
}

int main(int argc, char const *argv[]) {
    string buf;
    long ans = 0;
    bool enable = true;
    
    while(getline(cin, buf)) {
        const char *beg = buf.c_str(), *end = buf.c_str() + buf.length();
        for(; beg < end; ++beg) {
            if(strncmp(beg, "don't()", 7) == 0)
                enable = false;
            else if(strncmp(beg, "do()", 4) == 0)
                enable = true;
            else if(strncmp(beg, "mul(", 4) == 0) {
                beg += 4;

                std::string s;
                while(beg < end) {
                    s.push_back(*beg);
                    beg++;

                    if(!isdigit(*beg) && *beg != ',')
                        break;
                }

                if(*beg == ')') {
                    if(multiply(s)) {
                        cout << (enable? "  ": "    ") << s << endl;
                        if(enable)
                            ans += multiply(s);
                    }
                } else
                    beg--;
            }
        }
    }

    cout << ans << endl;

    return 0;
}