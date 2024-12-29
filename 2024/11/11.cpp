#include <bits/stdc++.h>
using namespace std;

#define N 75

string multiply(string num1, string num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    if(len1 == 0 || len2 == 0)
        return "0";

    vector<int> result(len1 + len2, 0);

    int i_n1 = 0; 
    int i_n2 = 0; 
    
    for(int i=len1-1; i>=0; i--) {
        int carry = 0;
        int n1 = num1[i] - '0';

        i_n2 = 0; 
                   
        for(int j=len2-1; j>=0; j--) {
            int n2 = num2[j] - '0';
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
            
            carry = sum/10;
            result[i_n1 + i_n2] = sum % 10;
            i_n2++;
        }

        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        i_n1++;
    }

    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
        i--;

    if (i == -1)
        return "0";

    string s = "";
    
    while (i >= 0)
        s += to_string(result[i--]);

    return s;
}

unordered_map<string, long> cache[N+1];

long solve(string e, int t) {
    if(t == 0)
        return 1;

    if(cache[t].contains(e)) {
        return cache[t][e];
    }
    else if(e == "0") {
        return cache[t][e] = solve("1", t - 1);
    }
    else if(e.size() % 2 == 0) {
        string s1(e.begin(), e.begin() + (e.size()/2));
        string s2(e.begin() + (e.size()/2), e.end());

        return cache[t][e] = (solve(s1, t - 1) + solve(multiply(s2, "1"), t - 1));
    }

    return cache[t][e] = solve(multiply(e, "2024"), t - 1);
}

int main(int argc, char const *argv[]) {
    int a;
    vector<int> nums;
    while(cin >> a)
        nums.push_back(a);

    long ans = 0;
    for(int i=0; i<nums.size(); ++i) {
        ans += solve(to_string(nums[i]), N);
    }

    cout << "Part 2 answer: " << ans << endl;

    return 0;
}