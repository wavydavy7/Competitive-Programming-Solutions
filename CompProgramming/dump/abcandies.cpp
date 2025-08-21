#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
using namespace std;
typedef long long ll;
int N, M;

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> M;
        int candies[M];
        int alice = 0;
        int bob = 0;
        int pt1 = 0;
        int pt2;
        int record = 0;
        int moves = 0;
        pt2 = M - 1;
        bool par = true;
        for (int j = 0; j < M; j++)
        {
            cin >> candies[j];
        }

        while (pt1 <= pt2)
        {
            int count = 0;
            if (par)
            {

                while (count <= record && pt1 <= pt2)
                {
                    count += candies[pt1];
                    pt1++;
                }

                alice += count;
            }
            else
            {
                while (count <= record && pt1 <= pt2)
                {
                    count += candies[pt2];
                    pt2--;
                }

                bob += count;
            }
            record = count;
            par = !par;
            moves++;
        }
        cout << moves << " " << alice << " " << bob << "\n";
    }
}