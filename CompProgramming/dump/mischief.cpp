#include "bits/stdc++.h"
using namespace std;
#define MAXN 300001 // use without semicolon
#define INF 10000000000000LL

int N, L;
int x[MAXN], y[MAXN]; // initialize arrays
int xid[MAXN], lis[MAXN];
long long dp[MAXN];

vector<int> levels[MAXN]; // levels include vector elements that can grow

bool cmpx(int a, int b)
{
    return x[a] < x[b];
}

void computeLIS() // the nlogn approach
{
    levels[0].push_back(xid[0]); // we process the lowest x coordinate
    lis[xid[0]] = 0;             // longest increasing sequence starting at xid[0], which is the lowest x coordinate
    int mx = 0;
    for (int i = 1; i < N; i++)
    {
        int cur = xid[i];
        int low = -1;
        int high = mx;
        while (low != high)
        {
            int mid = (low + high + 1) / 2; // ceiling function?
            if (y[levels[mid].back()] < y[cur])
            { // if the y coordinate corresponding to the last elem in levels[mid] is < corresponding y coordinate for cur
                low = mid;
            }
            else
            {
                high = mid - 1;
            }
        }
        levels[low + 1].push_back(cur); // gonna add cur to levels low + 1
        mx = max(mx, low + 1);          // update max value
        lis[cur] = low + 1;             // the cur in list is low + 1
    }
}

long long cost(int i, int j)
{
    return dp[i] + x[i] * ((long long)y[i]) - x[i] * ((long long)y[j]) - y[i] * ((long long)x[j]) + x[j] * ((long long)y[j]);
}

int findLocOvertake(int l, int i, int j)
{ // find when i overtakes j in level l, so everything past that point is better with i
    // in their shared range, i is better
    int low = 0;
    int high = levels[l].size();
    while (low != high)
    {
        int mid = (low + high) / 2;
        if (cost(i, levels[l][mid]) < cost(j, levels[l][mid]))
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    return low;
}
int firstDom[MAXN];
int lastDom[MAXN];

int findFirst(int l, int i) // find first point in level l dominating i in level l - 1
{
    int low = 0;
    int high = levels[l].size() - 1;
    while (low != high)
    {
        int mid = (low + high) / 2;
        if (x[levels[l][mid]] > x[i])
        {
            high = mid;
        }
        else
        {
            low = mid + 1;
        }
    }
    if (x[levels[l][low]] > x[i] && y[levels[l][low]] > y[i])
    {
        return low;
    }
    return -1;
}

int findLast(int l, int i)
{
    int low = 0;
    int high = levels[l].size() - 1;
    while (low != high)
    {
        int mid = (low + high + 1) / 2;
        if (y[levels[l][mid]] > y[i])
        {
            low = mid;
        }
        else
        {
            high = mid - 1;
        }
    }
    if (x[levels[l][low]] > x[i] && y[levels[l][low]] > y[i])
    {
        return low;
    }
    return -1;
}

int que[MAXN]; // queue?
int overtake[MAXN];
vector<int> level;

void solveStartingRegion(int l, int iStart, int iEnd, int qStart, int qEnd)
{
    int len = 0;
    int i = iStart;
    cout << "solveStartingRegion " << i << "\n";
    for (int j = qStart; j <= qEnd; j++)
    {
        int q = levels[l + 1][j];             // looking through l + 1 level
        while (i <= iEnd && firstDom[i] <= j) // is second condition rly necessary? yes because i can increase, process the relevant ones
        {
            while (len >= 2 && overtake[len - 2] <= findLocOvertake(l + 1, que[len - 1], level[i])) // while there's at least 2 elements and the last overtake is less than or equal to the last one in queue
            {
                cout << "subtracting from len\n";
                len--; // to simulate a monoqueue
            }
            que[len] = level[i];
            if (len >= 1) // if there's at least 2 elements, find overtake moment
            {
                overtake[len - 1] = findLocOvertake(l + 1, que[len - 1], level[i]); // find overtake of a point and the one after it
                cout << "This was added to overtake: " << overtake[len - 1];
            }
            len++;
            i++;
        }
        while (len >= 2 && overtake[len - 2] <= j) // while there's at least 2 elements and the overtaking point is less than some value between qstart and qend
        {
            len--; // simulate monoqueue
            cout << "subtracting from len(2)\n";
        }
        dp[q] = min(dp[q], cost(que[len - 1], q));
        cout << "dp of " << q << " is " << dp[q] << "\n";
    }
}
void solveEndingRegion(int l, int iStart, int iEnd, int qStart, int qEnd)
{
    int len = 0;
    int i = iEnd;
    cout << "solveEndingRegion";
    for (int j = qEnd; j >= qStart; j--)
    {
        int q = levels[l + 1][j]; // looking through l + 1 level
        while (i >= iStart && lastDom[i] >= j)
        {
            while (len >= 2 && overtake[len - 2] >= findLocOvertake(l + 1, level[i], que[len - 1]))
            {
                len--;
                cout << "subtracting from len\n";
            }
            que[len] = level[i];
            if (len >= 1)
            {
                overtake[len - 1] = findLocOvertake(l + 1, level[i], que[len - 1]);
                cout << "This was added to overtake: " << overtake[len - 1];
            }
            len++;
            i--;
        }
        while (len >= 2 && overtake[len - 2] > j)
        {
            len--;
            cout << "subtracting from len(2)\n";
        }
        dp[q] = min(dp[q], cost(que[len - 1], q));
        cout << "dp of " << q << " is " << dp[q] << "\n";
    }
}
int main()
{
    cin >> N >> L;
    for (int i = 0; i < N; i++) // you get your x coordinates and y coordinates
        cin >> x[i] >> y[i];
    x[N] = y[N] = L; // your last coordinate is your destination which you have to hit
    N++;
    for (int i = 0; i < N; i++) // you create N xids
        dp[i] = INF, xid[i] = i;

    sort(xid, xid + N, cmpx); // sort xid by x coordinates, index compression used

    computeLIS();
    for (vector<int> level : levels)
    {
        if (!level.empty())
        {
            cout << "new level \n";
            for (int num : level)
            {
                cout << num << " ";
            }
        }
    }

    for (int i = 0; i < levels[0].size(); i++)
    {
        int cur = levels[0][i];
        dp[cur] = x[cur] * ((long long)y[cur]);
    }
    for (int l = 0; levels[l + 1].size() > 0; l++)
    {
        level.clear();
        for (int i = 0; i < levels[l].size(); i++)
        {
            int cur = levels[l][i];
            int fd = findFirst(l + 1, cur);
            int ld = findLast(l + 1, cur);
            if (fd != -1)
            {
                firstDom[level.size()] = fd;
                lastDom[level.size()] = ld;
                level.push_back(levels[l][i]);
            }
        }
        // now your level contains everything in your current level
        for (int i = 0; i < level.size();)
        {
            int iEnd = i;
            while (iEnd < level.size() - 1 && firstDom[iEnd + 1] <= lastDom[i])
            {
                iEnd++;
            }
            solveStartingRegion(l, i, iEnd, firstDom[i], lastDom[i]);
            if (lastDom[iEnd] >= lastDom[i] + 1)
            {
                solveEndingRegion(l, i + 1, iEnd, lastDom[i] + 1, lastDom[iEnd]);
            }
            i = iEnd + 1;
        }
    }
    cout << dp[N - 1] << "\n";
}