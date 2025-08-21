#include <bits/stdc++.h>
//#include "../../algo/debug.h"
using namespace std;

int main(){
    int N;
    cin >> N;
    while (N--){
        int x;
        cin >> x;
        for (int i = 0; i < 5; i++){
            int cnt = x / (5 - i);
            if (x % (5 - i)) cnt++;
            for (int amt = 0; amt < cnt; amt++){
                if (i == 0) cout << 'a';
                else if (i == 1) cout << 'e';
                else if (i == 2) cout << 'i';
                else if (i == 3) cout << 'o';
                else cout << 'u';
            }
            x -= cnt;
        }
        cout << endl;
    }
}
