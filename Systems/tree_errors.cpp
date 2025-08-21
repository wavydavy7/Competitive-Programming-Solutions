
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    unordered_map<char, unordered_map<char, char>> adjList;
    char source, destination;
    long long maxWeight;

    vector<char> resPathNodes;

    enum ValidationErrors
    {
        E_OK = 0,
        E1 = 1, // Malformed input
        E2 = 2, // Logical input error
        E3 = 3  // No route found
    };
    ValidationErrors err = E_OK;

    string getErrorMessage(ValidationErrors err)
    {
        switch (err)
        {
        case E1: return "E1"; break;
        case E2: return "E2"; break;
        case E3: return "E3"; break;
        default: return "E_OK";
        }
    }

    bool isValidNode(char c)
    {
        return (c >= 'A' && c <= 'Z'); //has to be a character 
    }

    //*** ooh this is a really good idea ***
    // E1 - Syntax Error                      - DONE  (ToDo: Weight limit check)
    // E2 - Duplicate Definitions             - DONE
    //    - Target node definitions not found - DONE
    //    - Disconnected Graphs               - DONE
    //    - Multiple Routes                   -       (ToDo)
    // E3 - No Route Found                    - DONE

    void findSingleShortestPath(string& allPairs, string& targetPair)
    {

        // Step-1: Parse input to create adjacency list
        parseInput(allPairs, targetPair);
        if (err != E_OK)
        {
            cout << getErrorMessage(err);
            return;
        }

        // Step-2: Find shortest paths from source to all nodes, for a weighted undirected graph - Dijkstra's algorithm
        findShortestPathsUtil();
        if (err != E_OK)
        {
            cout << getErrorMessage(err);
            return;
        }

        // Step-3: Print the path
        string resPath;
        for (char node : resPathNodes)
        {
            if (!resPath.empty())
                resPath += "->";
            resPath += node;
        }
        cout << resPath;
    }

    void findShortestPathsUtil()
    {
        unordered_map<char, unsigned int> distance; // <node, shortest_distance>
        unordered_map<char, char> parent; // <node, parent>
        unordered_set<char> visited;

        for (auto const& [k, v] : adjList)
            distance[k] = UINT_MAX;
        distance[source] = 0;

        parent[source] = source;

        // <weight, node>
        set<pair<int, char>> s; // to simiulate min heap
        s.insert({ 0, source });
        while (!s.empty())
        {
            auto x = *(s.begin());
            s.erase(x);
            visited.insert(x.second);
            for (auto it : adjList[x.second]) // iterate through neighbors of this node
            {
                if (visited.count(it.first) == 0 &&
                    distance[it.first] > distance[x.second] + it.second)
                {
                    s.erase({distance[it.first], it.first});
                    distance[it.first] = distance[x.second] + it.second;
                    parent[it.first] = x.second;
                    s.insert({ distance[it.first], it.first });
                }
            }
        }

        if (visited.size() < adjList.size()) // if there are disconnected nodes, we can't reach them.
            err = E2;
        if (distance[destination] > maxWeight)
            err = E3;

        copyNodesToResult(parent, destination);
    }

    void copyNodesToResult(unordered_map<char, char>& parent, char node)
    {
        if (parent.count(node) == 0)
        {
            // Could not find parent
            err = E3;
            return;
        }

        if (node == source)
        {
            resPathNodes.push_back(node);
            return;
        }
        copyNodesToResult(parent, parent[node]);
        resPathNodes.push_back(node);
    }

    void parseInput(string& allPairs, string& targetPair)
    {
        int M = allPairs.size();
        int N = targetPair.size();

        if (M == 0 || N == 0 ||
            allPairs[0] == ' ' || allPairs[M -1] == ' ' ||      // no leading/trailing spaces allowed
            targetPair[0] == ' ' || targetPair[N-1] == ' ')   // no leading/trailing spaces allowed
        {
            err =  E1;
            return;
        }

        bool duplicateEdgesFound = false; // We cannot immediately throw E2, 
                                          // because we may find a E1 later. So hold your horses until everything is parsed.

        // 1) Parse all pairs
        int i = 0;
        while (i < M)
        {
            // Get next edge data; Format: (A,B,<number>)
            char s, d;
            long int w = 0;
            if (i + 6 < M
                && allPairs[i] == '['
                && isValidNode(allPairs[i + 1])
                && allPairs[i + 2] == ','
                && isValidNode(allPairs[i + 3])
                && allPairs[i + 4] == ','
                && isdigit(allPairs[i + 5]))
            {
                s = allPairs[i + 1];
                d = allPairs[i + 3];

                if ((adjList.count(s) > 0 && adjList[s].count(d) > 0) ||
                    (adjList.count(d) > 0 && adjList[d].count(s) > 0))
                    duplicateEdgesFound = true;

                i = i + 5; // now we are at first index of weight
                string num;
                while (i < M && isdigit(allPairs[i]))  // ToDo: Add a check to limit the number to max of unsigned int.
                    num += allPairs[i++];
                
                if ((i < M - 1 && allPairs[i] == ']' && allPairs[i + 1] == ' ') || // Not the last edge-pair
                    (i == M - 1 && allPairs[i] == ']'))                            // The last edge pair
                {
                    w = stol(num);
                    adjList[s][d] = w;
                    adjList[d][s] = w;
                    i = i + 2; // go to next edge pair
                }
                else //errrrrorrr
                {
                    err = E1;
                    return;
                }
            }
            //errorrrrr
            else
            {
                err = E1;
                return;
            }
        }

        // Parse Target Pair; Format:  A->D,<number> for the SPFA algorithm 
        i = 0;
        if (i + 5 < N
            && isValidNode(targetPair[i])
            && targetPair[i + 1] == '-'
            && targetPair[i + 2] == '>'
            && isValidNode(targetPair[i + 3])
            && targetPair[i + 4] == ','
            && isdigit(targetPair[i + 5]))
        {
            source = targetPair[i];
            destination = targetPair[i + 3];
            i = i + 5; // now we are at first index of weight
            string num;
            while (i < N && isdigit(targetPair[i]))  // ToDo: Add a check to limit the number to max of unsigned int.
                num += targetPair[i++];

            if (i == N)
            {
                maxWeight = stol(num);
            }
            else
            {
                err = E1;
                return;
            }
        }
        else
        {
            err = E1;
            return;
        }

        if (adjList.count(source) == 0 || adjList.count(destination) == 0 || duplicateEdgesFound)
            err = E2;
    }
};