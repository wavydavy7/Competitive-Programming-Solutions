#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
using namespace std;
typedef long long ll;
int N, M, D;

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> M >> D;
        int rem = D % (M - 1);
        int into = D / (M - 1);
        if (rem == 0)
        {
            rem = -1;
        }
        cout << into * M + rem << "\n";
    }
}