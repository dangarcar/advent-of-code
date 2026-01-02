#include "../../AOC.h"

struct op {
    string a, b, c;
    string op;
};

map<string, op> outs;
map<string, vector<op>> ins;
map<string, string> aliases;
int x, y;

bool solve(const string& s) {
    int i = (s[1]-'0')*10 + s[2]-'0';
    if(s[0] == 'x')
        return x & (1L << i);
    if(s[0] == 'y')
        return y & (1L << i);

    auto o = outs[s];
    if(o.op == "AND")
        return solve(o.a) and solve(o.b);
    if(o.op == "OR")
        return solve(o.a) or solve(o.b);
    if(o.op == "XOR")
        return solve(o.a) xor solve(o.b);

    return false;
}

void alias() {
    for(auto [k,v]: ins) {
        if(k[0] == 'x') {
            int i = (k[1]-'0')*10 + k[2]-'0';
            auto y = format("y{:02}", i);
            for(auto e: v) {
                if(e.b == y) {
                    auto a = format("{}{:02}", e.op, i);
                    if(aliases.contains(a) || aliases.contains(e.c)) {
                        cerr << "ERROR: " << a << ' ' << e.c << endl;
                        return;
                    }
                    aliases[a] = e.c;
                    aliases[e.c] = a;
                } else {
                    cerr << "ERROR: " << k << ' ' << e.c << endl;
                    return;
                }
            }
        }
    }

    aliases["CAR00"] = aliases["AND00"];

    for(int i=1; i<45; ++i) {
        auto k = format("XOR{:02}", i);

        auto carry = format("CAR{:02}", i-1);
        for(auto e: ins[aliases[k]]) {
            if(e.b == aliases[carry]) {
                if(e.c[0] == 'z') {
                    if(e.op != "XOR") {
                        cerr << "ERROR: " << k << ' ' << e.op << endl;
                        return;
                    }
                } else if(e.op == "AND"){
                    auto a = format("ICR{:02}", i);
                    aliases[a] = e.c;
                    aliases[e.c] = a;
                } else {
                    cerr << "ERROR: " << k << ' ' << e.op << endl;
                    return;
                }

            } else {
                cerr << "ERROR: " << k << ' ' << e.c << endl;
                return;
            }
        }

        k = format("AND{:02}", i);
        if(ins[aliases[k]].size() == 1) {
            auto o =ins[aliases[k]][0];
            if(o.op == "OR" && o.b == aliases[format("ICR{:02}", i)]) {
                auto a = format("CAR{:02}", i);
                aliases[o.c] = a;
                aliases[a] = o.c;
            } else {
                cerr << "ERROR: " << k << ' ' << o.op << ' ' << aliases[o.b] << endl;
                return;
            }
        } else {
            cerr << "ERROR: " << k << " too many inputs" << endl;
            return;
        }
    }

}

void printOP(op o) {
    cout << format("{}:{} {} {}:{} -> {}:{}\n", aliases[o.a], o.a,  o.op, aliases[o.b], o.b, aliases[o.c], o.c);
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string buf;
    x = 0; 
    y = 0;
    while(getline(cin, buf)) {
        if(buf.empty()) 
            break;
        int i = (buf[1]-'0')*10 + buf[2]-'0';
        if(buf[0] == 'x')
            x |= (static_cast<int>(buf[5]-'0') << i);
        if(buf[0] == 'y')
            y |= (static_cast<int>(buf[5]-'0') << i);
    }

    while(getline(cin, buf)) {
        if(buf.empty()) 
            continue;

        stringstream ss;
        ss << buf;

        op o;
        ss >> o.a;
        ss >> o.op;

        ss >> o.b;
        ss >> buf >> o.c;
        outs.insert({o.c, o});
        ins[o.a].push_back(o);
        
        swap(o.a, o.b);
        ins[o.a].push_back(o);
    }

    alias();

    for(int i=0; i<45; ++i) {
        auto x = format("x{:02}", i);
        for(auto e: ins[x])
            printOP(e);

        if(i != 0) {
            auto carry = format("CAR{:02}", i-1);
            for(auto e: ins[aliases[carry]]) {
                if(e.c[0] == 'z')
                    printOP(e);
                else
                    printOP(e);
            }

            auto o = outs[aliases[format("CAR{:02}", i)]];
            printOP(o);
        }

        cout << endl;
    }

    int ans = 0;
    for(auto [u, _]: outs) {
        if(u[0] == 'z') {
            int i = (u[1]-'0')*10 + u[2]-'0';
            //cout << u << ": " << solve(u) << "  " << i << endl;
            ans |= static_cast<int>(solve(u)) << i;
        }
    }

    cout << format("{}\n{}\n", x+y, ans);

    return 0;
}