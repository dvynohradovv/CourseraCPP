#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

string changeCapital(map <string, string>& capitalList);
string rename(map <string, string>& capitalList);
string about(map <string, string>& capitalList);
string dump(map <string, string>& capitalList);

int main()
{
	int Q;
	cin >> Q;
	string operation, exit;

	map <string, string> capitalList;

	for (int i = 0; i < Q; i++)
	{
		cin >> operation;
		if (operation == "CHANGE_CAPITAL")
		{
			exit += changeCapital(capitalList);
		}
		else if (operation == "RENAME")
		{
			exit += rename(capitalList);
		}
		else if (operation == "ABOUT")
		{
			exit += about(capitalList);
		}
		else if (operation == "DUMP")
		{
			exit += dump(capitalList);
		}

	}
	cout << exit;
	return 0;
}

string changeCapital(map <string, string>& capitalList)
{
	string country, new_capital, exit, old_capital;
	cin >> country >> new_capital;

	if (capitalList.count(country))
	{
		if (capitalList[country] == new_capital)
		{
			exit = "Country " + country + " hasn't changed its capital\n";
		}
		else
		{
			old_capital = capitalList[country];
			capitalList[country] = new_capital;
			exit = "Country " + country + " has changed its capital from " + old_capital + " to " + new_capital + "\n";
		}
	}
	else
	{
		capitalList[country] = new_capital;
		exit = "Introduce new country " + country + " with capital " + new_capital + "\n";
	}

	//cout << exit;
	return exit;
}

string rename(map <string, string>& capitalList)
{
	string old_country_name, new_country_name, exit, tmp;
	cin >> old_country_name >> new_country_name;
	
	if (old_country_name == new_country_name || !capitalList.count(old_country_name) || capitalList.count(new_country_name))
	{
		exit = "Incorrect rename, skip\n";
	}
	else
	{
		tmp = capitalList[old_country_name];
		capitalList.erase(old_country_name);
		capitalList[new_country_name] = tmp;
		exit = "Country " + old_country_name + " with capital " + tmp + " has been renamed to " + new_country_name + "\n";
	}
	
	//cout << exit;
	return exit;
}

string about(map <string, string>& capitalList)
{
	string country, tmp, exit;
	cin >> country;

	if (capitalList.count(country))
	{
		tmp = capitalList[country];
		exit = "Country " + country + " has capital " + tmp + "\n";
	}
	else
	{
		exit = "Country " + country + " doesn't exist\n";
	}

	//cout << exit;
	return exit;
}

string dump(map <string, string>& capitalList)
{
	string exit;

	if (capitalList.size() > 0)
	{
		for (auto item : capitalList)
		{
			exit += item.first + "/" + item.second + "\n";
		}
	}
	else
	{
		exit = "There are no countries in the world\n";
	}

	//cout << exit;
	return exit;
}