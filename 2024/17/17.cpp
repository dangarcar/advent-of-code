#include "../../AOC.h"

char run(long a, long b, long c, const string& prog) {
    for(int pc=0; pc<prog.size(); pc += 2) {
        long ins = prog[pc] - '0';
        long op = prog[pc+1] - '0';
        
        long comb = op;
        if(comb == 4) comb = a;
        else if(comb == 5) comb = b;
        else if(comb == 6) comb = c;

        switch(ins) {
            case 0: 
                a = a / (1LL << comb);
            break;

            case 1:
                b = b ^ op;
            break;

            case 2:
                b = comb % 8;
            break;

            case 3:
                if(a != 0) {
                    pc = op - 2;
                    //cout << a << ' ' << b << ' ' << c << endl;
                }
            break;

            case 4:
                b = b ^ c;
            break;

            case 5:
                return '0' + (comb % 8);
            break;

            case 6:
                b = a / (1LL <<  comb);
            break;

            case 7:
                c = a / (1LL << comb);
            break;
        }
    }

    return 0;
}

long solve(const string& prog, int i, long a) {
    if(i == 0) {
        return a;
    }

    for(long e=8*a; e < 8*(a+1); ++e) {
        if(run(e, 0, 0, prog) == prog[i-1]) {
            auto c = solve(prog, i-1, e);
            if(c != -1)
                return c;
        }
    }

    return -1;
}

signed main(signed argc, char* argv[]) {
    AoCTimer timer(argc, argv);
        
    string prog;
    long a, b, c;
    
    {
        string buf;
        getline(cin, buf);
        a = stol(string(buf.begin() + 11, buf.end()));
        getline(cin, buf);
        b = stol(string(buf.begin() + 11, buf.end()));
        getline(cin, buf);
        c = stol(string(buf.begin() + 11, buf.end()));

        getline(cin, buf);
        getline(cin, buf);
        stringstream ss;
        ss << buf;
        ss.ignore(8);
        int d;
        while (ss >> d) {
            prog += '0' + d;
            ss.ignore();
        }
    }

    /*cout << a << ' ' << b << ' ' << c << endl;
    for(auto e: prog)
        cout << e << ' ';
    cout << endl;*/

    while(a != 0) {
        auto out = run(a, b, c, prog);
        //cout << out << endl;
        a /= 8;
    }
    //cout << endl;

    cout << "Part 2 answer: " << solve(prog, prog.size(), 0) << endl;
    
    return 0;
}