//My Past
#include <cstdio> 
#include <iostream> 
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <E:\C语言\calendars\calendar.h>
#define MAX 1500

using namespace std;

class CALENDAR
{
public:
	char daily[MAX];
	int year, month, date;
	
public:
	CALENDAR()
	{}
	void reWrite(char _daily[MAX], int year, int month, int date);
	void cat(char tmp[]);
	int cmp(char tmp[]);
	void output();
	int kmp_search(char pattern[], int next[]);
}myPast[5000];

void CALENDAR :: reWrite(char _daily[MAX], int _year, int _month, int _date)
{
	strcpy(daily, _daily);
	year = _year;
	month = _month;
	date = _date;
}

int CALENDAR :: cmp(char tmp[])
{
	return strcmp(tmp, daily);
}
void CALENDAR :: cat(char tmp[])
{
	strcat(daily, tmp);
}

void CALENDAR :: output()
{
	cout << year << "年" << month << "月" << date << "日：" << daily << endl; 
}

int CALENDAR :: kmp_search(char pattern[], int next[])
{
	if(next == NULL) getNext(pattern, next);
	int * res = KMP(pattern, daily, next);
	//if(res[0]) output();
	return(res[0]);
}

int isNum(char c, char c1 = '0', char c2 = '0', char c3 = '0')
{
	return c <= '9' && c >= '0' && c1 <= '9' && c1 >= '0' && c2 <= '9' && c2 >= '0' && c3 <= '9' && c3 >= '0';
}

void proceed(char s[], int i, int &year, int &month, int &date)//把记事里的数字处理成日期 
{
	int m, n;
	year = month = date = 0;
	do
	{
		date *= 10;
		date += s[i++]-'0';
	}
	while(s[i] != '/');
	i++;
	do
	{
		month *= 10;
		month += s[i++]-'0';
	}
	while(s[i] != '/');
	i++;
	do
	{
		year *= 10;
		year += s[i++]-'0';
	}
	while(s[i] != ' ' && s[i] != '\t');
}


void readCalendars(char * filename, int & cnt)
{
	//2017-02-15 01:47:41
	//靠  才发现CALENDAR一直打错写成CALENDER了......
	 
	char s[MAX];
	char tmp[MAX], ctmp = 0;
	int lastDate = -1, lastMonth = -1, lastYear = -1;
	
	freopen(filename, "r", stdin);
	
	while(true)//cnt < 4303
	{
		int flag = 0;
		int year, month, date;
		int i = 0;
		gets(s);
		if(s[0] == '*')continue;
		for(i = 0;i < strlen(s);i++)
		{
			if(isNum(s[i], s[i+1], s[i+2], s[i+3]) && i > 3 && s[i-1] == '/')
			{
				while(isNum(s[i]) || s[i] == '/')
					i--;
				s[i] = 0;
				i++;
				proceed(s, i, year, month, date);
				flag = 1;
				break;
			}
		}
		if(flag == 0)//没有找到时间信息。。。再读一行 
		{ 
			do
			{
				gets(tmp);
				ctmp = getchar();
				if(ctmp == EOF)
					break;
				ungetch(ctmp);
				strcat(s, tmp);
				for(;i < strlen(s);i++)
				{
					if(isNum(s[i], s[i+1], s[i+2], s[i+3]) && i > 3 && s[i-1] == '/')
					{
						while(isNum(s[i]) || s[i] == '/')
							i--;
						s[i] = 0;
						i++;
						proceed(s, i, year, month, date);
						flag = 1;
						break;
					}
				}
			} while(flag == 0);
		} 
		if(ctmp == EOF)break;
		myPast[cnt].reWrite(s, year, month, date);
	//	myPast[cnt].output();
		if(lastDate == date && lastMonth == month && lastYear == year)
		{
			if(myPast[cnt-1].cmp(s) == 0)break;
			myPast[cnt-1].cat(s);
			
		}
		
		lastYear = year;
		lastMonth = month;
		lastDate = date;	
		cnt++;
	}
}
int main()
{
	void getIndex(int & index, int y, int m, int d, int cnt);
	
	int cnt = 0;
	//freopen("E:\\未分类品\\MyPast.txt", "r", stdin);//"rili.txt" 
	readCalendars("E:\\未分类品\\rili.txt", cnt);
	readCalendars("E:\\未分类品\\MyPast.txt", cnt);
	
	cout << "共读入" << cnt << "条日历" << endl;
//	system("pause");
	freopen("CON","r",stdin); 
	char p[MAX];
	while(~scanf("%s", p))
	{
		int * next = (int *)malloc(MAX*sizeof(int));
		getNext(p, next);
		for(int i = 0;i < cnt;i++)
		{
			if(myPast[i].kmp_search(p, next))
			{
				myPast[i].output();
				putchar('\n');
			}
		}
	}
	int year, month, date;
	while(~scanf("%d %d %d", &year, &month, &date)) 
	{
		for(int i = 0;i < cnt;i++)
		{
			if(myPast[i].year == year && myPast[i].month == month && myPast[i].date == date)
				myPast[i].output();
		}
	}
/*	
	int year = 0, month = 0, date = 0;
	while(~scanf("%d %d %d", &year, &month, &date))
	{
		int index = 0 ,printed = 0;
		while(index < cnt)
		{
			getIndex(index, year, month, date, cnt);
			if(index < 0) 
			{
				if(printed == 0) printf("*无此记事\n");
				break;
			}
			myPast[index++].output();
			printed++;
		}
	} */
}

void getIndex(int & index, int y, int m, int d, int cnt)//从 Index == index 开始，向后寻找标志日期事件 
{
	while(index < cnt)
	{
		if((myPast + index)->year == y && (myPast + index)->month == m && (myPast + index)->date == d) return;
		else index++;
	}
	if(index == cnt) index = -1;
	return;
}
