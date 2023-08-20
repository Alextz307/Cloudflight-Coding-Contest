#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
struct rectangle {
    string x1, y2, x2, y1;
};
 
int main() {
    /* int N;
    fin >> N; */
    vector < rectangle > a(1);
    for(auto& x : a) {
        string s;
        fin >> s;
        int p = 0;
        while(isdigit(s[p]) || s[p] == '.')
            x.x2.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            x.y2.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            x.x1.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            x.y1.push_back(s[p++]);
    }
    int T;
    fin >> T;
    int ans = 0;
    while(T--) {
        string s, lin, col;
        fin >> s;
        int p = 0;
        while(isdigit(s[p]) || s[p] == '.')
            lin.push_back(s[p++]);
        ++p;
        while(isdigit(s[p]) || s[p] == '.')
            col.push_back(s[p++]);
        bool ok = false;
        for(auto x : a)
            if(lin >= x.x1 && lin <= x.x2 && col >= x.y1 && col <= x.y2)
                ok = true;
        if(ok)
            ++ans;
    }
    fout << ans;
}
 
