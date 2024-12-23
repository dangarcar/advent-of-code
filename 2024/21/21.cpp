#include <bits/stdc++.h>
using namespace std;

#define INTER 25

const char* numpad[] = { "789","456", "123", " 0A" };
vector<vector<vector<string>>> numpadPaths;

const char* kb[] = {" ^A", "<v>"};
vector<vector<vector<string>>> kbPaths;

unordered_map<string, long> cache[INTER];

vector<string> path(char a, char b){
    int ai = a - '0', bi = b-'0';
    
    if(a == 'A') 
        ai = 10;
    if(b == 'A')
        bi = 10;
    
    return numpadPaths[ai][bi];
}

void calculateNumpadPaths() {
    numpadPaths.assign(11, vector<vector<string>>(11, vector<string>()));

    for(int i=0; i<4; ++i) {
        for(int j=0; j<3; ++j) {
            auto c = numpad[i][j];
            if(c == ' ') continue;
            int ci = c - '0';
            if(c == 'A') ci = 10; 

            for(int k=0; k<4; ++k) {
                for(int l=0; l<3; ++l) {
                    auto c2 = numpad[k][l];
                    if(c2 == ' ') continue;
                    int c2i = c2 - '0';
                    if(c2 == 'A') c2i = 10;

                    string dy(abs(i-k), (i-k)>0? '^':'v');
                    string dx(abs(j-l), (j-l)>0? '<':'>');

                    auto s1 = dy + dx, s2 = dx + dy;

                    if(numpad[k][j] != ' ')
                        numpadPaths[ci][c2i].push_back(s1 + "A");
                    if(numpad[i][l] != ' ' && s1 != s2)
                        numpadPaths[ci][c2i].push_back(s2 + "A");
                }
            }
        }
    }
}

int kbIndex(char c) {
    int i=0;
    switch (c) {
        case 'A': i=0; break;
        case '^': i=1; break;
        case '<': i=2; break;
        case '>': i=3; break;
        case 'v': i=4; break;
    }

    return i;
}

void calculateKbPaths() {
    kbPaths.assign(5, vector<vector<string>>(5, vector<string>()));

    for(int i=0; i<2; ++i) {
        for(int j=0; j<3; ++j) {
            auto c = kb[i][j];
            if(c == ' ') continue;
            int ci = kbIndex(c);

            for(int k=0; k<2; ++k) {
                for(int l=0; l<3; ++l) {
                    auto c2 = kb[k][l];
                    if(c2 == ' ') continue;
                    int c2i = kbIndex(c2);

                    string dy(abs(i-k), (i-k)>0? '^':'v');
                    string dx(abs(j-l), (j-l)>0? '<':'>');

                    auto s1 = dy + dx, s2 = dx + dy;

                    if(kb[k][j] != ' ')
                        kbPaths[ci][c2i].push_back(s1 + "A");
                    if(kb[i][l] != ' ' && s1 != s2)
                        kbPaths[ci][c2i].push_back(s2 + "A");
                }
            }
        }
    }
}

vector<string> kbPath(char a, char b) {
    return kbPaths[kbIndex(a)][kbIndex(b)];
}

long solve(string s, int depth) {
    if(depth == 0)
        return s.size();

    if(cache[depth-1].count(s))
        return cache[depth-1][s];

    long ans = 0;
    char lc = 'A';
    for(auto c: s) {
        long pos = 1e18;
        for(auto e: kbPath(lc, c))
            pos = min(solve(e, depth-1), pos);

        ans += pos;
        lc = c;
    }

    return cache[depth-1][s] = ans;
}

int main(int argc, char const *argv[]) {
    string buf;
    vector<string> input;
    vector<long> nums;
    while(getline(cin, buf)) {
        if(buf.empty()) continue;

        input.push_back(buf);
        nums.push_back(stoi(string(buf.begin(), buf.end()-1)));
    }

    auto start = chrono::steady_clock::now();

    calculateNumpadPaths();
    calculateKbPaths();

    long ans = 0;
    for(int i=0; i<input.size(); ++i) {
        long best = 0;
        
        char lc = 'A';
        for(auto c: input[i]) {
            long pos = 1e18;
            for(const auto e: path(lc, c))
                pos = min(solve(e, INTER), pos);

            best += pos;
            lc = c;
        }
        
        cout << input[i] << ' ' << best << endl;
        ans += nums[i] * best;
    }

    auto dt = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start);
    printf("\n%ld\n%.03fms\n", ans, dt.count() / 1000.0);

    return 0;
}