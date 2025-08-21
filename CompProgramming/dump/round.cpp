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
        int counter = 1;
        vector<int> nums;
        while (M > 0)
        {
            if (M % 10 != 0)
            {
                nums.push_back((counter) * (M % 10));
            }
            counter *= 10;
            M -= M % 10;
            M /= 10;
        }

        cout << nums.size() << "\n";
        for (int num : nums)
        {
            cout << num << " ";
        }
        cout << "\n";
    }
}