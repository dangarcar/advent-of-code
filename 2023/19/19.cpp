#include "../../AOC.h"

using Entry = array<pair<int,int>, 4>;

struct Instruction {
    char v;
    char sym;
    int w;
    string next;
};

struct InstructionSet {
    vector<Instruction> ins;
    string def;
};

map<string, InstructionSet> instructions;
map<char, int> xmas = { {'x', 0}, {'m', 1}, {'a', 2}, {'s', 3} };

int solve(const string& insName, Entry e) {
    if(insName == "A")
        return accumulate(e.begin(), e.end(), 1L, [](int acc, const auto& r){
            return acc * max(0LL, r.second - r.first +1);
        });
    else if(insName == "R")
        return 0L;

    const auto& inSet = instructions[insName];
    int ans = 0L;
    for(auto ins: inSet.ins) {
        Entry ne = e;
        auto i = xmas[ins.v];

        if(ins.sym == '>' && e[i].second > ins.w) {
            ne[i] = make_pair(ins.w+1, e[i].second);
            e[i] = make_pair(e[i].first, ins.w);
        }
        else if(e[i].first < ins.w) {
            ne[i] = make_pair(e[i].first, ins.w-1);
            e[i] = make_pair(ins.w, e[i].second);
        }

        ans += solve(ins.next, ne);
    }

    ans += solve(inSet.def, e);

    return ans;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
    
    string str;
    while(getline(cin, str)) {
        if(str.empty()) break;

        char c;
        istringstream iss(std::move(str));
        string name;
        while(iss >> c, c != '{') 
            name += c;

        InstructionSet inSet;
        while(getline(iss, str, ',')) {
            if(*str.rbegin() == '}') {
                inSet.def = string(str.begin(), str.end()-1);
                instructions[name] = inSet;
                break;
            }

            istringstream tokenizer(std::move(str));
            Instruction in;
            in.v = tokenizer.get();
            in.sym = tokenizer.get();
            tokenizer >> in.w;
            tokenizer.ignore();
            tokenizer >> in.next;

            inSet.ins.push_back(in);
        }
    }

    int ans = solve("in", Entry {
        make_pair(1,4000),
        make_pair(1,4000),
        make_pair(1,4000),
        make_pair(1,4000),
    });
    

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}
