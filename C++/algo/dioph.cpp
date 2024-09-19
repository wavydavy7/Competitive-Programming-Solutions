#include "bits/stdc++.h"
#define pb push_back
using namespace std;

int x, y, d;
int n = 234;
int gcd(int a, int b){return b == 0 ? a : gcd(b, a % b);}

void dio(int a, int b){
    if (b == 0) {
        x = 1;
        y = 0;
        d = a;
        return;
    }
	dio(b, a%b);
	//back propagation
	int cpy = y;
	y = x - (a/b)*y;
	x = cpy;
}

int main(){
    dio(25, 18);
    cout << x << " " << y << "\n";
    int factor = 839 / gcd(25, 18);
    cout << x * factor + (18/d) * n << " " << y * factor - (25/d) * n << "\n";
}