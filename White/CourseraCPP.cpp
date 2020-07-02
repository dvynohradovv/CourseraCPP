#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <sstream>
#include <set>
#include <map>

using namespace std;

string AskTimeServer();

class TimeServer {
public:
    string GetCurrentTime() 
    {
		try {
            last_fetched_time = AskTimeServer();
            return last_fetched_time;
		}
		catch (const system_error& er) {
            return last_fetched_time;
		}
        catch (...) {
            throw;
        }
    }
private:
    string last_fetched_time = "00:00:00";
};

int main() 
{
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    }
    catch (exception & e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}

string AskTimeServer() 
{

}