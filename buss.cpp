#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
void NEW_BUS(map<string, vector<string>>& busList, map<string, vector<string>>& stopList);
string BUSES_FOR_STOP(map<string, vector<string>>& stopList);
string STOPS_FOR_BUS(map<string, vector<string>>& busList, map<string, vector<string>>& stopList);
string ALL_BUSES(map<string, vector<string>>& busList);



int main()
{
    int Q;
    cin >> Q;

    map<string, vector<string>> busList;
    map<string, vector<string>> stopList;

    string request, exit;
    for (int i = 0; i < Q; i++)
    {
        cin >> request;

        if (request == "NEW_BUS")
        {
            NEW_BUS(busList, stopList);
        }
        else if (request == "BUSES_FOR_STOP")
        {
            exit += BUSES_FOR_STOP(stopList);
        }
        else if (request == "STOPS_FOR_BUS")
        {
            exit += STOPS_FOR_BUS(busList, stopList);
        }
        else if (request == "ALL_BUSES")
        {
            exit += ALL_BUSES(busList);
        }

    }

    cout << exit;
    return 0;
}

void NEW_BUS(map<string, vector<string>>& busList, map<string, vector<string>>& stopList)
{
    string bus, stop;
    int stop_count;
    cin >> bus >> stop_count;
    while (stop_count)
    {
        cin >> stop;
        busList[bus].push_back(stop);
        stopList[stop].push_back(bus);
        stop_count--;
    }
}

string BUSES_FOR_STOP(map<string, vector<string>>& stopList)
{
    string stop, exit;
    cin >> stop;
    if (!stopList.count(stop))
    {
        return "No stop\n";
    }
    for (auto& item : stopList[stop])
    {
        exit += item + " ";
    }
    exit += "\n";
    return exit;
}

string STOPS_FOR_BUS(map<string, vector<string>>& busList, map<string, vector<string>>& stopList)
{
    string bus, exit, tmp;
    cin >> bus;
    if (!busList.count(bus))
    {
        return "No bus\n";
    }

    for (auto& it1 : busList[bus])
    {
        exit += "Stop " + it1 + ": ";
        tmp = "";
        for (auto& it2 : stopList[it1])
        {
            if (it2 != bus)
            {
                tmp += it2 + " ";
            }
        }
        if (tmp == "")
        {
            tmp = "no interchange";
        }
        exit += tmp + "\n";
    }
    return exit;
}

string ALL_BUSES(map<string, vector<string>>& busList)
{
    string exit;
    if (busList.size() == 0)
    {
        return "No buses\n";
    }

    for (auto& item : busList)
    {
        exit += "Bus " + item.first + ": ";
        for (auto& it : item.second)
        {
            exit += it + " ";
        }
        exit += "\n";
    }
    return exit;
}


