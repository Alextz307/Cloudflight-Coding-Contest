#include <bits/stdc++.h>
 
using namespace std;
 
ifstream fin("text.in");
ofstream fout("text.out");
 
int main() {
    int Y;
    fin >> Y;
    int T;
    fin >> T;
    while(T--) {
        int x, y;
        fin >> x >> y;
        if((y < Y && Y > 0) || (y > Y && Y < 0))
            fout << x << ' ' << y << ' ';
    }
}
 
