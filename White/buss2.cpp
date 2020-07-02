#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

int main()
{
    int Q;
    cin >> Q;

    map <vector<string>, int> stopList;
    vector<string> tempVec;

    string exit;
    for (int i = 0, N, numberBus = 1; i < Q; i++)
    {
        cin >> N;
        tempVec.resize(N);
        for (int i = 0; i < N; i++)
        {
            cin >> tempVec[i];
        }
        
        if (stopList.count(tempVec))
        {
            exit += "Already exists for " + to_string(stopList[tempVec]) + "\n";
        }
        else
        {
            stopList[tempVec] = numberBus;
            exit += "New bus " + to_string(numberBus) + "\n";
            numberBus++;
        }
        tempVec.clear();
    }

    cout << exit;
}
