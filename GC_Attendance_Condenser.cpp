#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

void ReplaceAll(string&, const string&, const string&);

int main(void)
{
	cout << "Global Conflict Attendance Condenser\n" << endl;
	cout << "For when things go wrong with the GC TS3 Attendance Tracker" << endl;
	cout << "and the list needs condensing." << endl;
	cout << "But you probably can't even read this\n"<< endl;

	cout << "Condensing List . . . ";
	ifstream cli;
	string nextname;
	vector<string> names;

	cli.open("Clients.txt");
	if(!cli.is_open())
	{
		cout << "No Clients.txt found" << endl;
		cout << "Press a key then Enter to continue" << endl;
		char go;
		cin >> go;
		return 0;
	}

	getline(cli, nextname);
	names.push_back(nextname);

	int len;
	bool same = false;
	while(!nextname.empty())
	{
		getline(cli, nextname);
		if(!nextname.empty())
		{
			len = strlen(nextname.c_str());
			same = false;
			//check for #/#
			if(len > 1 && nextname.substr(len - 2, 1) == "/")
			{
				nextname = nextname.substr(0, len-4);
				Sleep(1);
				//check for extra \s
				len = strlen(nextname.c_str());
				if(len > 1 && nextname.substr(len - 2, 2) == "\\s")
				{
					nextname = nextname.substr(0, len-2);
					Sleep(1);
				}
			}
			//check for #/## or ##/##
			else if(len > 2 && nextname.substr(len - 3, 1) == "/")
			{
				nextname = nextname.substr(0, len-5);
				Sleep(1);
				//check for extra 1
				len = strlen(nextname.c_str());
				if(nextname.substr(len - 1, 1) == "1")
				{
					nextname = nextname.substr(0, len-1);
					Sleep(1);
					len = strlen(nextname.c_str());
				}
				//check for extra \s
				if(len > 1 && nextname.substr(len - 2, 2) == "\\s")
				{
					nextname = nextname.substr(0, len-2);
					Sleep(1);
				}
			}
			//check for \s#
			else if(len > 2 && nextname.substr(len - 3, 1) == "\\")
			{
				nextname = nextname.substr(0, len-3);
				Sleep(1);
			}
			//check for \s##
			else if(len > 3 && nextname.substr(len - 4, 1) == "\\")
			{
				nextname = nextname.substr(0, len-4);
				Sleep(1);
			}
			//check for (#)
			else if(nextname.substr(len-1, 1) == ")")
			{
				nextname = nextname.substr(0, len-3);
				Sleep(1);
				//check for extra ( if (##)
				len = strlen(nextname.c_str());
				if(nextname.substr(len - 1, 1) == "(")
				{
					nextname = nextname.substr(0, len-1);
					Sleep(1);
					len = strlen(nextname.c_str());
				}
				//check for extra \s
				if(len > 1 && nextname.substr(len - 2, 2) == "\\s")
				{
					nextname = nextname.substr(0, len-2);
					Sleep(1);
				}
			}
			//check for the same name
			for(int j = 0; j < names.size(); j++)
			{
				if(nextname == names[j])
				{
					same = true;
					break;
				}
			}
			//if not the same, add to vector
			if(!same)
			{
				names.push_back(nextname);
			}
		}
	}
	cli.close();

	//remove "\s" and replace with " "
	const string bad = "\\s";
	const string good = " ";
	for(int i = 0; i < names.size(); i++)
	{
		ReplaceAll(names[i], bad, good);
	}

	//Get Date
	time_t now = time(0);
	tm* localtm = localtime(&now);
	//and make file name
	stringstream filename;
	filename << "AttendanceRecovery-"
			 << localtm->tm_year + 1900 << "-"
			 << localtm->tm_mon + 1 << "-"
			 << localtm->tm_mday
			 << ".txt";

	ofstream atten;
	atten.open(filename.str());
	for(int i = 0; i < names.size(); i++)
	{
		atten << names[i] << endl;
	}
	atten.close();
	cout << "Complete!" << endl;

	return 0;
}

void ReplaceAll(string &str, const string& from, const string& to)
{
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos)
	{
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return;
}