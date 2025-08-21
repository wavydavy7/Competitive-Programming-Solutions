#include <iterator>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <array>
#include <string>
using namespace std;

vector<int> arr;

void lps(string p)
{
    int ptr1 = 0;
    int ptr2 = 1;
    arr.push_back(0); // this is your lps array
    while (ptr2 < p.length())
    {

        if (p[ptr1] == p[ptr2])
        {
            ptr1++;
        }
        else
        {
            while (p[ptr1] != p[ptr2] && ptr1 > 0) // say they're not equal... then we 
            {
                ptr1 = arr[ptr1 - 1]; //ptr2 doesn't match...but maybe mmmx might match so we roll back to the previous of what did match till ptr1... and see if it works 
            }
        }
        arr.push_back(ptr1);
        ptr2++; //we're always incrementing this 
    }
}
int cnt_amt(string w, string p)
{
    int ptrw = 0;
    int ptrp = 0; //this is the pattern 
    int cnt = 0;
    while (ptrw < w.length())
    {
        while (ptrp && p[ptrp] != w[ptrw])
        {
            ptrp = arr[ptrp - 1];
        }
        if (w[ptrw] == p[ptrp])
        {
            if (ptrp == p.length() - 1)
            {
                cnt++;
                ptrp = arr[ptrp];
            }
            else
            {
                ptrp++;
            }
        }
        ptrw++; //you always increment this
    }
    return cnt;
}
int main()
{
    string word;
    string pattern;
    cin >> word >> pattern;
    lps(pattern);
    // for (int i = 0; i < arr.size(); i++)
    // {
    //     cout << arr[i] << " ";
    // }
    cout << cnt_amt(word, pattern);
}