/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 *$ Written by Ryan Morris (K3rb3ros) $
 *$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
 * for CSCI 470                        
 * prints the current date in the format DD-MMM-YYYY using a system API to get the date
 */

#include <iostream>
#include <time.h>
#include <string>
using namespace std;

string get_month(tm* tm_date)//return the month in 3 letter abbrieviated string form from the tm structure
{
	int month = tm_date->tm_mon + 1;
	string month_str = "";
	if(tm_date != NULL)
	{
		switch (month)
			{
			case 1:
				month_str = "JAN";
				break;
			case 2:
				month_str = "FEB";
				break;
			case 3:
				month_str = "MAR";
				break;
			case 4:
				month_str = "APR";
				break;
			case 5:
				month_str = "MAY";
				break;
			case 6:
				month_str = "JUN";
				break;
			case 7:
				month_str = "JUL";
				break;
			case 8:
				month_str = "AUG";
				break;
			case 9:
				month_str = "SEP";
				break;
			case 10:
				month_str = "OCT";
				break;
			case 11:
				month_str = "NOV";
				break;
			case 12:
				month_str = "DEC";
				break;
			default: month_str = "Error retrieving month";
				break;
		}
	}
	return month_str;
}

int get_day(tm* tm_date) //return the date from the tm structure in integer form
{
	int day = tm_date->tm_mday;
	if(tm_date == NULL) day = -1; //return negative value to indicate error
	return day;
}

int get_year(tm* tm_date)
{
	int ad_year = tm_date->tm_year + 1900;
	if(tm_date == NULL)
	{
		ad_year = -1;
	}
	return ad_year;
}

//int main(int argc, char** argv)
int main()
{
	time_t TIME; //declare a time object/struct
	struct tm* date; //Set up a tm structure to get all the useful info from it
	time(&TIME); //populate time with the current system time
	date = localtime(&TIME); //populate the tm struct with the current system time
	
	//Call fancy functions to format the output and check for errors
	cout << get_day(date) << "-" << get_month(date) << "-" << get_year(date) << endl;
	
	return 0;
}