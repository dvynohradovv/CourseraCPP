#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

class Person
{
public:
    //Person() {}
    Person(const string& f, const string& l, const int& y)
    {
        f_Name = f;
        ChangeFirstName(y, f);
        l_Name = l;
        ChangeLastName(y, l);
        zero_Year = y;
    }

    void ChangeFirstName(const int& year, const string& first_name)
    {
        fName_List[year] = first_name;
    }
    void ChangeLastName(const int& year, const string& last_name)
    {
        lName_List[year] = last_name;
    }
    string GetFullName(const int& year)const
    {
        if (!PersonExistOrNot(year)) {
            return "No person";
        }
        int trash = 0;
        string first_name = NamesForYear(year, fName_List, trash);
        string last_name = NamesForYear(year, lName_List, trash);
        return ReturnNames(first_name, last_name);
    }
    string GetFullNameWithHistory(const int& year)const
    {
        if (!PersonExistOrNot(year)) {
            return "No person";
        }
        string first_name = PastNamesForYear(year, fName_List);
        string last_name = PastNamesForYear(year, lName_List);
        return ReturnNames(first_name, last_name);
    }

private:
    string NamesForYear(const int& year, const map<int, string>& Name_List, int& currYear)const
    {
        string name;
        currYear = year;
        if (Name_List.empty()) {
            return name;
        }
        int tmp = Name_List.begin()->first;
        for (const auto& it : Name_List) {
            if (it.first > year) {
                break;
            }
            tmp = it.first;
        }
        if (tmp <= year) {
            currYear = tmp;
            name = Name_List.at(tmp);
        }
        return name;
    }
    string PastNamesForYear(const int& year, const map<int, string>& Name_List)const
    {
        int currYear = year;
        string name = NamesForYear(year, Name_List, currYear);
        string past_names;
        vector<string> tmpV;
        for (const auto& it : Name_List) {
            if (it.first >= currYear) {
                break;
            }
            else {
                if (!count(begin(tmpV), end(tmpV), it.second)) {
                    tmpV.push_back(it.second);
                }
                if (year != currYear && tmpV.front() == name) {
                    tmpV.erase(begin(tmpV));
                }
            }
        }
        reverse(begin(tmpV), end(tmpV));
        if (!tmpV.empty() && !name.empty() && tmpV.front() == name) {
            tmpV.erase(begin(tmpV));
        }
        for (const auto& it : tmpV) {
            past_names += it;
            if (it != tmpV.back()) {
                past_names += ", ";
            }
            else {
                name += " (" + past_names + ")";
            }
        }
        return name;
    }
    string ReturnNames(const string& first_name, const string& last_name) const
    {
        if (first_name.empty() && last_name.empty()) {
            return "Incognito";
        }
        else if (first_name.empty()) {
            return last_name + " with unknown first name";
        }
        else if (last_name.empty()) {
            return first_name + " with unknown last name";
        }
        else {
            return first_name + " " + last_name;
        }
    }
    bool PersonExistOrNot(const int& year)const
    {
        if (year < zero_Year) {
            return false;
        }
        return true;
    }

    map<int, string> fName_List;
    map<int, string> lName_List;
    string f_Name;
    string l_Name;
    int zero_Year = 0;
};

int main()
{
    Person person("Polina", "Sergeeva", 1960);
    for (int year : {1959, 1960}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1965, "Appolinaria");
    person.ChangeLastName(1967, "Ivanova");
    for (int year : {1965, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    return 0;
}