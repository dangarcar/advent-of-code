#include "../../AOC.h"

struct op {
    string a, b, c;
    string op;
};

unordered_map<string, op> outs;
unordered_map<string, vector<pair<string, bool>>> ins;
unordered_map<string, string> aliases;
int x, y;

void printOP(op o) {
    char buf[64];
    snprintf(buf,  64, "%s:%s %s %s:%s -> %s:%s\n", 
        aliases[o.a].c_str(), o.a.c_str(),  o.op.c_str(), aliases[o.b].c_str(), o.b.c_str(), aliases[o.c].c_str(), o.c.c_str());

    cout << static_cast<const char*>(buf);
}

string opName(const char* name, int n) {
    char buf[8];
    snprintf(buf, 8, "%s%02lld", name, n);
    return string(buf);
}

bool alias(int i) {
    string xork, andk;
    string carryk = aliases[opName("CAR", i-1)];;
    
    //ALIAS THE XOR AND THE AND
    for(auto [e, sw]: ins[opName("x", i)]) {
        auto o = outs.at(e);
        if(sw) swap(o.a, o.b);

        if(o.op == "AND")
            andk = o.c;
        else if (o.op == "XOR")
            xork = o.c;
        else 
            return false;
    }

    assert(!andk.empty() && !xork.empty());
    aliases[andk] = opName("AND", i);
    aliases[aliases[andk]] = andk;
    aliases[xork] = opName("XOR", i);
    aliases[aliases[xork]] = xork;

    //ALIAS THE INTERMIDIATE CARRY AND THE OUTPUT
    for(auto [e, sw]: ins[xork]) {
        auto o = outs.at(e);
        if(sw) swap(o.a, o.b);

        if(o.b == carryk) {
            if(o.c[0] == 'z') {
                if(o.op != "XOR")
                    return false;
            } 
            else if(o.op == "AND"){
                auto a = opName("ICR", i);
                aliases[a] = o.c;
                aliases[o.c] = a;
            } 
            else
                return false;

        } else 
            return false;
    }

    //ALIAS THE CARRY
    if(ins[andk].size() == 1) {
        auto [ok, sw] = *ins[andk].begin();
        auto o = outs.at(ok);
        if(sw) swap(o.a, o.b);

        if(o.op == "OR" && o.b == aliases[opName("ICR", i)]) {
            auto a = opName("CAR", i);
            aliases[o.c] = a;
            aliases[a] = o.c;
        } else 
            return false;
    } else 
        return false;

    return true;
}

vector<string> getOuts(int i) {
    vector<string> v;

    auto x = opName("x", i);
    for(auto e: ins[x])
        v.push_back(e.first);

    if(i != 0) {
        auto carry = opName("CAR", i-1);
        for(auto e: ins[aliases[carry]])
            v.push_back(e.first);

        if(aliases.contains(opName("CAR", i)))
            v.push_back(aliases[opName("CAR", i)]);
    }

    if(find(v.begin(), v.end(), opName("z",i)) == v.end()) {
        v.push_back(opName("z",i));
    }

    return v;
}

void swapOuts(const string& xs, const string& ys) {
    auto &x = outs[xs], &y = outs[ys];

    swap(aliases[aliases[xs]], aliases[aliases[ys]]);
    swap(aliases[xs], aliases[ys]);

    x.c = ys;
    for(auto& e: ins[x.a]) if(e.first == xs) { e.first = ys; break; }
    for(auto& e: ins[x.b]) if(e.first == xs) { e.first = ys; break; }

    y.c = xs;
    for(auto& e: ins[y.a]) if(e.first == ys) { e.first = xs; break; }
    for(auto& e: ins[y.b]) if(e.first == ys) { e.first = xs; break; }

    swap(x, y);
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
        if(o.a >= o.b) 
            swap(o.a, o.b);

        outs.insert({o.c, o});
        
        ins[o.a].push_back({o.c, false});
        ins[o.b].push_back({o.c, true});
    }

    for(auto [e, sw]: ins["x00"]) {
        if(outs[e].op == "AND") {
            aliases[e] = "AND00";
            aliases["AND00"] = e;
            aliases["CAR00"] = e;
        } 
        else if (outs[e].op == "XOR") {
            aliases[e] = "XOR00";
            aliases["XOR00"] = e;
        }
    }

    vector<string> changes;
    for(int t=1; t<45; ++t) {
        auto v = getOuts(t);
        if(alias(t)) {
            goto end;
        }

        for(int i=0; i<v.size(); ++i) {
            for(int j=i+1; j<v.size(); ++j) {
                if(v[i].empty() || v[j].empty()) 
                    continue;

                swapOuts(v[i], v[j]);

                if(alias(t)) {
                    changes.push_back(v[i]);
                    changes.push_back(v[j]);
                    goto end;
                }

                swapOuts(v[i], v[j]);
            }
        }
        
        end:;
    }

    sort(changes.begin(), changes.end());
    string ans;
    for(auto e: changes)
        ans += e + ",";
    cout << "Part 2 answer: " << string(ans.begin(), ans.end()-1) << endl;

    return 0;
}