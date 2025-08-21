#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main()
{
    int N, S;
    cin >> N >> S;

    unordered_map<int, pair<int, int>> mp;
    int direction = 1;
    int size = 1;
    int cnt = 0;
    vector<int> visited(N, 0);

    for (int i = 0; i < N; ++i)
    {
        int q, v;
        cin >> q >> v;
        mp[i] = {q, v};
    }

    int init = S - 1;
    while (init >= 0 && init < N)
    {
        if (mp[init].first && mp[init].second <= size && !visited[init])
        {
            cnt++;
            visited[init] = 1;
        }
        else if (mp[init].first == 0)
        {
            direction *= -1;
            size += mp[init].second;
        }
        init += direction * size;
    }

    cout << cnt << endl;
    return 0;
}