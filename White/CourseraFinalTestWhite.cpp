#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cctype>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Date {
public:
    Date() 
    {
        year = 0;
        month = 0;
        day = 0;
    }
    Date(const string& str) {
        SetDate(str);
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
    void SetDate(const string& exit) {
        istringstream ss(exit);
        int y, m, d;
        char separator1, separator2;
        ss >> y;
        ss >> separator1;
        ss >> m;
        ss >> separator2;
        ss >> d;
        if (!ss.eof() || exit.size() < 5 || (separator1 != '-' || separator2 != '-')) throw invalid_argument("Wrong date format: " + exit);
        else if (m > 12 || m < 1) throw invalid_argument("Month value is invalid: " + to_string(m));
        else if (d > 31 || d < 1) throw invalid_argument("Day value is invalid: " + to_string(d));
        year = y;
        month = m;
        day = d;

    }
private:
    int year;
    int month;
    int day;
};

bool operator<(const Date& lhs, const Date& rhs) 
{
    return (lhs.GetYear() * 372 + lhs.GetMonth() * 31 + lhs.GetDay()) < (rhs.GetYear() * 372 + rhs.GetMonth() * 31 + rhs.GetDay());
}

bool operator>(const Date& lhs, const Date& rhs)
{
    return !(lhs < rhs);
}

bool operator==(const Date& lhs, const Date& rhs)
{
    if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay()) {
        return true;
    }
    return false;
}

class Database {
public:
    void AddEvent(const Date& date, const string& event) 
    {
        database[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const string& event)
    {
        if (database.count(date)) {
            if (database[date].count(event)) {
                database[date].erase(event);
                return true;
            }
        }
        return false;
    }
    int  DeleteDate(const Date& date) 
    {
        int count = database[date].size();
        database.erase(date);
        return count;
    }
    void Find(const Date& date) const
    {
        if (database.count(date))
        {
            for (const auto& i : database.at(date)) {
                cout << i << endl;
            }
        }
    }
    void Print() const
    {
        cout << setfill('0');
        for (const auto& i : database) {
            for (const auto& j : i.second) {
                cout << setw(4) << i.first.GetYear() << "-" << setw(2) << i.first.GetMonth() << "-" << setw(2) << i.first.GetDay() << " " << j << endl;
            }
        }
    }
private:
    map<Date, set<string>> database;
};

int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        if (!command.empty()) {
            istringstream ss(command);
            try {
                Date date;
                string operation, cur_date, event;
                ss >> operation;
                if (operation == "Add") {
                    ss >> cur_date;
                    date.SetDate(cur_date);
                    ss >> event;
                    db.AddEvent(date, event);
                }
                else if (operation == "Del") {
                    ss >> cur_date;
                    date.SetDate(cur_date);
                    if (!ss.eof()) {
                        ss >> event;
                        bool result = db.DeleteEvent(cur_date, event);
                        if (result == true) cout << "Deleted successfully" << endl;
                        else cout << "Event not found" << endl;
                    }
                    else {
                        cout << "Deleted " + to_string(db.DeleteDate(cur_date)) + " events" << endl;
                    }
                }
                else if (operation == "Find") {
                    ss >> cur_date;
                    date.SetDate(cur_date);
                    db.Find(cur_date);
                }
                else if (operation == "Print") {
                    db.Print();
                }
                else {
                    throw invalid_argument("Unknown command: " + operation);
                }
            }
            catch (const invalid_argument& er) {
                cout << er.what() << endl;
                break;
            }
        }
    }

    return 0;
}