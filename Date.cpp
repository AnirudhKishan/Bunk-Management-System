#include "Date.h"
#include <ctime>

		#include<iostream>

// Defining Setters and Getters : BEGIN

void Date::set_date ( short unsigned int val )
{
	date = val;
}
void Date::set_month ( short unsigned int val )
{
	month = val;
}
void Date::set_year ( short unsigned int val )
{
	year = val;
}

short unsigned int Date::get_date ( void )
{
	return date;
}
short unsigned int Date::get_month ( void )
{
	return month;
}
short unsigned int Date::get_year ( void )
{
	return year;
}

std::string Date::get_day ( void )
{
	return day;
}

// Defining Setters and Getters : END

void Date::calc_day ( void )
{
	time_t time_now;
	time(&time_now);

	tm time_now_struct;
	time_now_struct = *( localtime ( &time_now ) ) ;
	short unsigned int today_day_num;
	today_day_num = time_now_struct.tm_wday;
	sanitize(time_now_struct);

	tm stored_time_as_struct;
	convert_to_structure ( stored_time_as_struct );

	short unsigned int day_diff;
	short int day_num;

	if ( mktime(&time_now_struct) >= mktime(&stored_time_as_struct) )
	{
		day_diff = ( difftime ( mktime(&time_now_struct), mktime(&stored_time_as_struct) ) ) / ( 60 * 60 * 24 ) ;
		day_num = today_day_num - (day_diff%7);
		if (day_num < 0)
		{
			day_num = 7 + day_num;
		}

	}
	else
	{
		//std::cout<<"\t\tHERE"; std::cin.get();
		day_diff = ( difftime ( mktime(&stored_time_as_struct), mktime(&time_now_struct) ) ) / ( 60 * 60 * 24 ) ;
		day_num = today_day_num + (day_diff%7);
		if (day_num > 6)
		{
			day_num = day_num - 7;
		}

	}

	//std::cout<<"Daydiff : "<<day_diff;

	//std::cout<<"\n\tDAY : "<<day_num<<" "<<date<<month<<year<<std::endl;// std::cin.get();

	switch (day_num)
	{
		case 0 :	day = "Sunday"; break;
		case 1 :	day = "Monday"; break;
		case 2 :	day = "Tuesday"; break;
		case 3 :	day = "Wednesday"; break;
		case 4 :	day = "Thursday"; break;
		case 5 :	day = "Friday"; break;
		case 6 :	day = "Saturday"; break;
	}
}

short unsigned int Date::get_day_as_int ( void )
{
	if ( day == "Monday" )
		return 0;
	else if ( day == "Tuesday" )
		return 1;
	else if ( day == "Wednesday" )
		return 2;
	else if ( day == "Thursday" )
		return 3;
	else if ( day == "Friday" )
		return 4;
	else if ( day == "Saturday" )
		return 5;
	else if ( day == "Sunday" )
		return 6;
	else
	return 7;
}

void Date::sanitize ( tm& time_struct )
{
	time_struct.tm_sec = time_struct.tm_min	= time_struct.tm_hour = time_struct.tm_wday = time_struct.tm_yday = time_struct.tm_isdst = 0;
	time_struct.tm_gmtoff = 0;
	time_struct.tm_zone = "";
}

void Date::set_today ( void )
{
	time_t time_now;
	time ( &time_now );

	tm time_now_struct;
	time_now_struct = *( localtime ( &time_now ) );

	convert_from_structure ( time_now_struct );

	calc_day();
}

void Date:: convert_to_structure ( tm& time_struct )
{
	time_struct.tm_mday = date;
	time_struct.tm_mon = (month) - 1;
	time_struct.tm_year = (year) - 1900;

	sanitize(time_struct);
}

void Date:: convert_from_structure ( tm time_struct )
{
	date = time_struct.tm_mday;
	month = time_struct.tm_mon + 1;
	year = time_struct.tm_year + 1900;
}

void Date::write_to_file ( std::ofstream& fout )
{
	fout<<std::endl<<day<<std::endl<<date<<std::endl<<month<<std::endl<<year;
}

void Date::read_from_file ( std::ifstream& fin )
{
	getline(fin,day);
	fin>>date; fin.get();
	fin>>month; fin.get();
	fin>>year; fin.get();
}

bool Date::operator == ( Date right )
{
	if ( (date==right.date) && (month==right.month) && (year==right.year) )
		return true;
	else
		return false;
}

bool Date::operator < ( Date right )
{
	if ( year < right.year)
		return true;
	else if ( year==right.year && month<right.month )
		return true;
	else if ( year==right.year && month==right.month && date<right.date )
		return true;
	else
		return false;
}

bool Date::operator > ( Date right )
{
	if ( year > right.year)
		return true;
	else if ( year==right.year && month>right.month )
		return true;
	else if ( year==right.year && month==right.month && date>right.date )
		return true;
	else
		return false;
}

bool Date::operator <= ( Date right )
{
	if ( year < right.year)
		return true;
	else if ( year==right.year && month<right.month )
		return true;
	else if ( year==right.year && month==right.month && date<right.date )
		return true;
	else if ( year==right.year && month==right.month && date==right.date )
		return true;
	else
		return false;
}

bool Date::operator >= ( Date right )
{
	if ( year > right.year)
		return true;
	else if ( year==right.year && month>right.month )
		return true;
	else if ( year==right.year && month==right.month && date>right.date )
		return true;
	else if ( year==right.year && month==right.month && date==right.date )
		return true;
	else
		return false;
}

Date Date::operator ++ ()
{
	date++;

	if ( month==2 && ( ( (year%4) && date==29 ) || ( !(year%4) && date==30 ) ) )
	{
		date = 1;
		month++;
	}
	else if ( ( month==4 || month==6 || month==9 || month==11 ) && date==31 )
	{
		date = 1;
		month++;
	}
	else if ( ( month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12) && date==32 )
	{
		date = 1;
		month++;
	}

	if ( month==13 )
	{
		month = 1;
		year++;
	}

	calc_day();

	//std::cout<<"\n++ date gives"<<get_date()<<" "<<get_month()<<" "<<get_year()<<" as "<<get_day()<<std::endl; std::cin.get();

	//std::cout<<"\n\t"<<get_day()<<" "<<get_date()<<" "<<get_month()<<" "<<get_year()<<std::endl; std::cin.get();

	return *this;

}
