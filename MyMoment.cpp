#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<vector>
#include<map>
#include<cstdlib>

#define rep(i, s, n) for(size_t i = s; i < n; i++)

using namespace std;

class Calendar
{
public:
	string daily;
	int year, month, date;
} moment[10][13][12];

int main()
{
	freopen("myMoment.txt", "r", stdin);
	
	int c_y = 0, c_m = 0, c_d = 0;		// current year, month, date
	bool loaded[10][13][32]; memset(loaded, 0, sizeof(loaded));
	string line;
	int cnt = 0;
	
	while(getline(cin, line))
	{
	//	cout << line << endl;
		//cout << '*'<< line.substr(0, 7) << endl;
		if(line == "BEGIN:VEVENT" ) 
		{
			cnt++;
			getline(cin, line);
			getline(cin, line);
			string context = line.substr(8);
			getline(cin, line);
			getline(cin, line);
			int colonIndex = line.find(":");
			//if (colonIndex != 26) cout << line << endl;
			string dateStr = line.substr(colonIndex + 1, 8);
			int dateNum = atoi(dateStr.c_str());
			c_y = dateNum / 10000; c_m = dateNum % 10000 / 100; c_d = dateNum % 100;
			
			Calendar nC;
			nC.daily = context;
			nC.date = c_d; nC.month = c_m; nC.year = c_y; 
			if(loaded[c_y - 2015][c_m][c_d] && 0)
			{
				moment[c_y - 2015][c_m][c_d].daily += "\n" + context;
				cout << c_y << ' ' << c_m << ' ' << c_d << endl;
				cout << moment[c_y - 2015][c_m][c_d].daily << endl << endl;
			}
			else
			{
				moment[c_y - 2015][c_m][c_d] = nC;
			}
			loaded[c_y - 2015][c_m][c_d] = 1;
			
			if(0 && !(rand() % 50))
			{
				cout << c_y << ' ' << c_m << ' ' << c_d << endl;
				cout << nC.daily << endl << endl;
			}
		}
	}
	for(int i = 2; i < 3; i++) {
		for(int j = 1; j <= 12; j++) {
			for(int k = 1; k <= 31; k++) {
				if(loaded[i][j][k] == 0) {
					cout << i+2015 << ' ' << j << ' ' << k << endl;
				}
			}
		}
	}
}
