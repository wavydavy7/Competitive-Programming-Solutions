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
        if (M % 2 && D % 2 == 0)
        {
            cout << "NO\n";
        }
        else if ((M % 2 && D % 2) || (M % 2 == 0 && D % 2 == 0))
        {
            if (D > M)
            {
                cout << "NO\n";
            }
            else
            {
                cout << "YES\n";
                for (int i = 1; i < D; i++)
                {
                    cout << "1 ";
                }
                cout << (M - (D - 1)) << "\n";
            }
        }
        else
        {
            if (M < 2 * D)
            {
                cout << "NO\n";
            }
            else
            {
                cout << "YES\n";
                for (int i = 1; i < D; i++)
                {
                    cout << "2 ";
                }
                cout << (M - 2 * (D - 1)) << "\n";
            }
        }
    }
}