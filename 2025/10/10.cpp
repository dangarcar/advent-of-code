#include "../../AOC.h"


struct Test {
    vector<vector<int>> moves;
    vector<int> reqs;

    vector<vector<double>> extended;
};  

constexpr double EPS = 1e-4;

vector<vector<int>> A;
int n, m;
int ans = 1e9;


bool isInteger(double b) {
    return abs(b - (int)b) < EPS || abs(b - (int)b) > 1-EPS;
}

int totalCases = 0, correctCases = 0;

int sub(int i, vector<int>& sol, int sum, const int top) {
    if(i < 0)
        return sum;


    int jc = -1, lib = 0;
    for(int j=0; j<sol.size(); ++j) {
        if(A[i][j] == 0) 
            continue;

        if(sol[j] == -1) {
            jc = j;
            lib++;
        }
    }

    if(lib == 0) {
        int a = 0;
        for(int j=0; j<sol.size(); ++j) {
            if(A[i][j] != 0 && sol[j] != -1)
                a += sol[j] * A[i][j];
        } 

        if(a == A[i].back())
            ans = min(ans, sub(i-1, sol, sum, top));
    } else if(lib == 1) {
        int a = 0;
        for(int j=0; j<sol.size(); ++j) {
            if(j != jc && A[i][j] != 0)
                a += sol[j] * A[i][j];
        } 

        auto b = (A[i][sol.size()] - a) / A[i][jc];
        auto bmod = (A[i][sol.size()] - a) % A[i][jc];
        if(bmod == 0 && b >= 0) {
            sol[jc] = b;

            if(sum + sol[jc] < ans)
                ans = min(ans, sub(i-1, sol, sum + sol[jc], top));

            sol[jc] = -1;
        }
    } else if(lib > 1) {
        for(int a=0; a<=top; ++a) {
            if(sum + a >= ans)
                break;
            
            sol[jc] = a;

            ans = min(ans, sub(i, sol, sum + a, top));

            sol[jc] = -1;
        }
    } else {
        cout << "AAAA\n";
    }

    return ans;
}


int solve(Test& t) {
    auto& B = t.extended;
    
    n = B.size(), m = B[0].size();
    int mult = 1;
    for(int k=0; k<n; ++k) {
        sort(B.begin()+k, B.end(), [k](auto& a, auto& b) { return abs(a[k]) > abs(b[k]); });
    
        for(int i=k+1; i<n; ++i) {
            if(B[i][k] == 0) continue;

            auto c = B[i][k] / B[k][k];
            for(int j=k; j<m; ++j)
                B[i][j] -= c*B[k][j];

            int a = 1;
            while(isInteger(c*a) == false)
                a++;
            mult *= a;
        }
    }

    A.assign(n, vector<int>(m));
    for(int i=0; i<n; ++i)
        for(int j=0; j<m; ++j)
            A[i][j] = round(mult * B[i][j]);

    vector<int> sol(t.moves.size(), -1);
    ans = 1e9;
    sub(n-1, sol, 0, *max_element(t.reqs.begin(), t.reqs.end()));

    return ans;
}


signed main() {
    AoCTimer timer;

    string buf;    
    vector<Test> tests;
    while(getline(cin, buf)) {
        istringstream iss(buf);
        string s;
        iss >> s;
        Test t;

        while(iss >> s, s[0] != '{'){
            vector<int> v;
            for(int i=1; i<s.size(); i+=2)
                v.push_back(s[i] - '0');
            t.moves.push_back(v);
        }

        iss = istringstream(string(s.begin()+1, s.end()-1));
        char ch;
        int a;
        while(iss >> a) {
            t.reqs.push_back(a);
            iss >> ch;
        }


        t.extended.assign(t.reqs.size(), vector<double>(t.moves.size()+1, 0));
        for(int j=0; j<t.moves.size(); ++j) {
            for(auto i: t.moves[j])
                t.extended[i][j] = 1;
        }

        for(int i=0; i<t.reqs.size(); ++i) {
            t.extended[i].back() = t.reqs[i];
        }


        tests.push_back(t);
    }

    int ans = 0;
    for(int i=0; i<tests.size(); ++i) {
        int a = solve(tests[i]);
        ans += a;
    }

    cout << "Part 2 answer: " << ans << '\n';

    return 0;
}