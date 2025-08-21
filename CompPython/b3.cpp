#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> arr[i];
    }

    int cnt = 0;

    for (int i = 0; i < N; ++i)
    {
        int temp = arr[i] < 0 ? -arr[i] : arr[i];
        cnt += temp;
        for (int j = i + 1; j < N; ++j)
        {
            arr[j] += (j - i + 1) * -arr[i];
        }
    }

    cout << cnt;
}
