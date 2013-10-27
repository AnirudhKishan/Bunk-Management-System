#include "Bunker.h"
#include <fstream>

//Defining Setters and Getters : BEGIN
void Bunker::set_no_of_subjects (short unsigned int val)
{
	no_of_subjects = val;
}
short unsigned int Bunker::get_no_of_subjects (void)
{
	return no_of_subjects;
}

void Bunker::set_no_of_periods (short unsigned int val)
{
	no_of_periods = val;
}
short unsigned int Bunker::get_no_of_periods (void)
{
	return no_of_periods;
}

void Bunker::set_subject_names (std::vector<std::string> val)
{
	subject_names = val;
}
std::vector<std::string> Bunker::get_subject_names (void)
{
	return subject_names;
}

void Bunker::set_time_table (std::vector< std::vector<short unsigned int> > val)
{
	time_table = val;
}
std::vector< std::vector<short unsigned int> > Bunker::get_time_table (void)
{
	return time_table;
}

void Bunker::set_total_no_of_bunks ( short unsigned int val )
{
	total_no_of_bunks = val;
}
short unsigned int Bunker::get_total_no_of_bunks ( void )
{
	return total_no_of_bunks;
}

void Bunker::set_total_attendance ( float val )
{
	total_attendance = val;
}
float Bunker::get_total_attendance ( void )
{
	return total_attendance;
}

void Bunker::set_no_of_bunks_per_subject (std::vector<short unsigned int> val)
{
	no_of_bunks_per_subject = val;
}
std::vector<short unsigned int> Bunker::get_no_of_bunks_per_subject (void)
{
	return no_of_bunks_per_subject;
}

std::vector< std::vector<Date> > Bunker::get_date_of_bunk_per_subject_per_bunk ( void )
{
	return date_of_bunk_per_subject_per_bunk;
}

void Bunker::set_attendance_per_subject (std::vector<float> val)
{
	attendance_per_subject = val;
}
std::vector<float> Bunker::get_attendance_per_subject (void)
{
	return attendance_per_subject;
}

void Bunker::set_free_days (std::vector<bool> val)
{
	free_days = val;
}
std::vector<bool> Bunker::get_free_days (void)
{
	return free_days;
}

void Bunker::set_min_attendance_per_subject ( std::vector<float> val )
{
	min_attendance_per_subject = val;
}
std::vector<float> Bunker::get_min_attendance_per_subject ( void )
{
	return min_attendance_per_subject;
}

void Bunker::set_total_min_attendance ( float val )
{
	total_min_attendance = val;
}
float Bunker::get_total_min_attendance ( void )
{
	return total_min_attendance;
}

void Bunker::set_starting_date ( Date val )
{
	starting_date = val;
}
Date Bunker::get_starting_date ( void )
{
	return starting_date;
}
Date& Bunker::obtain_starting_date ( void )
{
	return starting_date;
}
//Defining Setters and Getters : END

//Definition of File Handeling Methods : BEGIN
void Bunker::write_to_file (void)
{
	short unsigned int i, j;

	ofstream fout;
	fout.open("datafile", ios::app);

	fout<<endl<<"<!--start--!>";

	fout<<endl<<name;

	fout<<endl<<password;

	fout<<endl<<no_of_subjects;

	fout<<endl<<no_of_periods;

	for (i=0; i<no_of_subjects; i++)
		fout<<endl<<subject_names[i];

	for (i=0; i<7; i++)
		for (j=0; j<no_of_periods; j++)
			fout<<endl<<time_table[i][j];

	/*
	for (i=0; i<7; i++)
		fout<<endl<<no_of_periods_per_day_per_subject[i];
	*/

	/*
	fout<<endl<<total_no_of_bunks;
	*/

	/*
	fout<<endl<<total_attendance;
	*/

	for (i=0; i<no_of_subjects; i++)
		fout<<endl<<no_of_bunks_per_subject[i];

	for (i=0; i<no_of_subjects; i++)
	{
		for (j=0; j<no_of_bunks_per_subject[i]; j++)
		{
			date_of_bunk_per_subject_per_bunk[i][j].write_to_file ( fout );
		}
	}

	/*
	for (i=0; i<no_of_subjects; i++)
		fout<<endl<<attendance_per_subject[i];
	*/

	for (i=0; i<7; i++)
		fout<<endl<<free_days[i];

	for (i=0; i<no_of_subjects; i++)
		fout<<endl<<min_attendance_per_subject[i];

	fout<<endl<<total_min_attendance;

	starting_date.write_to_file(fout);

	fout.close();

}

short unsigned int Bunker::read_from_file (string val)
{
	int i, j;

	Bunker obj_temp;
	string str;
	int integer;

	ifstream fin;
	fin.open("datafile");

	if (!fin)
	{
		fin.close();
		return 1;		//File did not open succesfully
	}

	while (!fin.eof())
	{

		getline(fin,str);

		if (str=="<!--start--!>")
		{

			getline(fin,obj_temp.name);

			if (obj_temp.name == val)
			{
				getline(fin,obj_temp.password);

				fin>>obj_temp.no_of_subjects; fin.get();		//to remove trailing endline

				fin>>obj_temp.no_of_periods; fin.get();

				for (i=0; i<obj_temp.no_of_subjects; i++)
					getline(fin,obj_temp.subject_names[i]);

				for (i=0; i<7; i++)
					for (j=0; j<obj_temp.no_of_periods; j++)
						fin>>obj_temp.time_table[i][j]; fin.get();

				/*
				for (i=0; i<7; i++)
					fin>>obj_temp.no_of_periods_per_day_per_subject; fin.get();
				*/
				obj_temp.calculate_no_of_periods_per_day_per_subject();

				/*
				fin>>obj_temp.total_no_of_bunks; fin.get();
				*/

				/*
				fin>>obj_temp.total_attendance; fin.get();
				*/

				for (i=0; i<obj_temp.no_of_subjects; i++)
					fin>>obj_temp.no_of_bunks_per_subject[i]; fin.get();

				obj_temp.calculate_total_no_of_bunks();

				for (i=0; i<obj_temp.no_of_subjects; i++)
				{
					for (j=0; j<obj_temp.no_of_bunks_per_subject[i]; j++)
					{
						obj_temp.date_of_bunk_per_subject_per_bunk[i][j].read_from_file ( fin );
					}
				}

				/*
				for (i=0; i<obj_temp.no_of_subjects; i++)
					fin>>obj_temp.attendance_per_subject[i]; fin.get();
				*/

				for (i=0; i<7; i++)
				{
					fin>>integer; fin.get();
					obj_temp.free_days[i] = ( integer==0 ? false : true);
				}

				for (i=0; i<obj_temp.no_of_subjects; i++)
				{
					fin>>obj_temp.min_attendance_per_subject[i]; fin.get();
				}

				fin>>obj_temp.total_min_attendance; fin.get();

				obj_temp.starting_date.read_from_file(fin);

				if (obj_temp.starting_date.get_month()!=0)
				{
					Date today;
					today.set_today();
					obj_temp.calculate_attendance ( obj_temp.starting_date, today );
				}

				*this = obj_temp;

				fin.close();
				return 0;
			}
			else
				continue;
		}
		else
			continue;
	}

	fin.close();
	return 2;
}

void Bunker::write_to_file_at_position ( void )
{
	//This goes on same like the Bunker::read_from_file() method, until the required object is found
	//Then it behaves like the Bunker::write_to_file() method.
	int i, j;

	Bunker obj_temp;
	string str;

	ifstream fin;
	fin.open("datafile");
	ofstream fout;
	fout.open("temp_datafile");

	fin.seekg(1);

	while (!fin.eof())
	{
		getline(fin,str); fout<<endl<<str;

		if (str=="<!--start--!>")
		{
			getline(fin,obj_temp.name); fout<<endl<<obj_temp.name;
			if (obj_temp.name == name)
			{
				//Writing Behaviour : BEGIN

				fout<<endl<<password;

				fout<<endl<<no_of_subjects;

				fout<<endl<<no_of_periods;

				for (i=0; i<no_of_subjects; i++)
					fout<<endl<<subject_names[i];

				for (i=0; i<7; i++)
					for (j=0; j<no_of_periods; j++)
						fout<<endl<<time_table[i][j];

				/*
				for (i=0; i<7; i++)
					fout<<endl<<no_of_periods_per_day_per_subject[i];
				*/

				/*
				fout<<endl<<total_no_of_bunks;
				*/

				/*
				fout<<endl<<total_attendance;
				*/

				for (i=0; i<no_of_subjects; i++)
					fout<<endl<<no_of_bunks_per_subject[i];

				for (i=0; i<no_of_subjects; i++)
				{
					for (j=0; j<no_of_bunks_per_subject[i]; j++)
					{
						date_of_bunk_per_subject_per_bunk[i][j].write_to_file ( fout );
					}
				}

				/*
				for (i=0; i<no_of_subjects; i++)
					fout<<endl<<attendance_per_subject[i];
				*/

				for (i=0; i<7; i++)
					fout<<endl<<free_days[i];

				for (i=0; i<no_of_subjects; i++)
					fout<<endl<<min_attendance_per_subject[i];

				fout<<endl<<total_min_attendance;

				starting_date.write_to_file(fout);

				//Writing Behaviour : END

				//Going to the end of the this record in the input stream : BEGIN
				getline(fin,str);
				while ( !fin.eof() || str=="<!--start--!>")
					getline(fin,str);
				//Going to the end of the this record in the input stream : END

				//putting to the rest of the input stream to the output stream : BEGIN
				while ( !fin.eof() )
				{
					fout<<endl<<str;
					getline(fin,str);
				}
				//putting to the rest of the input stream to the output stream : END
			}
			else
				continue;
		}
		else
			continue;
	}

	fin.close(); fout.close();

	remove("datafile");
	rename("temp_datafile","datafile");

}
//Definition of File Handeling Methods : END

void Bunker::calculate_total_no_of_bunks ( void )
{
	short unsigned int i;
	total_no_of_bunks = 0;
	for ( i=0; i<no_of_subjects; i++)
	{
		total_no_of_bunks += no_of_bunks_per_subject[i];
	}
}

void Bunker::register_bunk ( short unsigned int subject_index, Date date_of_bunk )
{
	//Increasing the number of bunkes in the specified subjet : BEGIN
	no_of_bunks_per_subject[subject_index] ++;
	//Increasing the number of bunkes in the specified subjet : END
	//Assigning the specified date_of_bunk to this bunk : BEGIN
	date_of_bunk_per_subject_per_bunk[subject_index][ (no_of_bunks_per_subject[subject_index]-1) ] = date_of_bunk;
	//Assigning the specified date_of_bunk to this bunk :

	//recalculate attendance for today : BEGIN
	Date today;
	today.set_today();

	calculate_attendance ( starting_date, today );
	//recalculate attendance for today : END

	//writing the updated values to file : BEGIN
	write_to_file_at_position ();
	//writing the updated values to file : END

}

void Bunker::calculate_attendance ( Date from, Date to)
{
	//calculating as to how many days have passed since the first day : BEGIN
	tm to_struct;
	tm from_struct;

	to.convert_to_structure ( to_struct );
	from.convert_to_structure ( from_struct );

	short unsigned int day_diff;
	day_diff  = ( difftime ( mktime(&to_struct), mktime(&from_struct) ) ) / ( 60 * 60 * 24 );
	day_diff++;
	//cout<<"DD : "<<day_diff; cin.get();															//have to consider BOTH ectreme dates
	//calculating as to how many days have passed since the first day : END

	//finding out the starting day : BEGIN
	string from_day_string = from.get_day();
	short unsigned int from_day_int;
	if (from_day_string=="Monday")
		from_day_int = 0;
	else if (from_day_string=="Tuesday")
		from_day_int = 1;
	else if (from_day_string=="Wednesday")
		from_day_int = 2;
	else if (from_day_string=="Thursday")
		from_day_int = 3;
	else if (from_day_string=="Friday")
		from_day_int = 4;
	else if (from_day_string=="Saturday")
		from_day_int = 5;
	else if (from_day_string=="Sunday")
		from_day_int = 6;
	//finding out the starting day : END

	//calculating total number of periods since from date for each subject and total: BEGIN
	short unsigned int i, j;
	vector<short unsigned int> total_no_of_periods_per_subject(25,0);
	short unsigned int total_no_of_periods=0;

	for (i=0; i<day_diff; i++)
	{
		for (j=0; j<no_of_subjects; j++)
		{
			total_no_of_periods_per_subject[j] += no_of_periods_per_day_per_subject[from_day_int][j];
		}

		from_day_int++;
		from_day_int %= 7;
	}

	for (i=0; i<no_of_subjects; i++)
	{
		total_no_of_periods += total_no_of_periods_per_subject[i];
	}
	//calculating total number of periods since from date for each subject and total: END

	//calculating number of bunks in the given date range : BEGIN
	calculate_no_of_bunks_in_date_range( from, to );
	//calculating number of bunks in the given date range :

	//calculating attendance per subject : BEGIN
	for (i=0; i<no_of_subjects; i++)
	{
		attendance_per_subject[i] = ( total_no_of_periods_per_subject[i] - no_of_bunks_per_subject[i] ) / (float)total_no_of_periods_per_subject[i];
		attendance_per_subject[i] *= 100;		//converting to percentage
	}
	//calculating attendance per subject : END

	//calculating total attendance : BEGIN
	total_attendance = (total_no_of_periods - total_no_of_bunks) / (float)total_no_of_periods;
	total_attendance *= 100;		//converting to percentage
	//calculating total attendance : END

}

void Bunker::calculate_no_of_periods_per_day_per_subject ( void )
{
	int i, j;

	for (i=0; i<7; i++)
	{
		for (j=0; j<no_of_periods; j++)
		{
			if ( time_table[i][j] == 0)
				continue;
			else
			{
				no_of_periods_per_day_per_subject[i][(time_table[i][j]-1)]++;
			}
		}
	}
}

void Bunker::calculate_no_of_bunks_in_date_range ( Date from, Date to )
{
	short unsigned int i, j;
	short unsigned int no_of_bunks;

	total_no_of_bunks = 0;

	for (i=0; i<no_of_subjects; i++ )
	{
		no_of_bunks = no_of_bunks_per_subject[i];
		no_of_bunks_per_subject[i] = 0;
		for ( j=0; j<no_of_bunks; j++)
		{
			if ( date_of_bunk_per_subject_per_bunk[i][j]>=from && date_of_bunk_per_subject_per_bunk[i][j]<=to )
				no_of_bunks_per_subject[i]++;
		}

		total_no_of_bunks += no_of_bunks_per_subject[i];

	}

}

void copy ( string from_string, string to_string )
{
	const char *from = from_string.c_str ();
	const char *to = to_string.c_str ();

	ifstream fin;
	fin.open( from );

	ofstream fout;
	fout.open( to );

	string str;

	getline(fin,str);		//to ignore the first newline in the file
	while ( !fin.eof() )
	{
		getline(fin,str);
		fout<<endl<<str;
	}

	fin.close();
	fout.close();
}

short unsigned int Bunker::suggest_bunks ( short unsigned int subject_index, Date to )
{
	copy("datafile", "temp_datafile");

	rename ( "datafile", "datafile1");
	rename ( "temp_datafile", "datafile");

	short unsigned int no_of_bunks = 0;

	Date today;
	today.set_today();

	calculate_attendance(starting_date, to);
	while ( attendance_per_subject[subject_index] >= min_attendance_per_subject[subject_index] )
	{
		register_bunk(subject_index, today);
		calculate_attendance(starting_date, to);
		//cout<<"\nAPS : "<<attendance_per_subject[subject_index]<<"\t\tMIN : "<<min_attendance_per_subject[subject_index]<<endl; cin.get();
		no_of_bunks++;
	}

	remove ("datafile");
	rename ("datafile1", "datafile");

	if ( no_of_bunks==0)
		return 0;
	else
		return (no_of_bunks-1);

}

short unsigned int Bunker::suggest_bunks ( short unsigned int subject_index, Date to, vector<Date>& Dates, short unsigned int mode )
{

	if ( mode == 0 )		//starting period
	{
		//cout<<"\nSuggest Bunks called with Start of Day and subject_index : "

		Date iterator;
		iterator.set_today();

		short unsigned int no = 0;

		for ( ; iterator<=to; ++iterator )
		{
			if ( time_table[iterator.get_day_as_int()][0] == (subject_index+1) )		//subject_index+1 because in the time_table '0' means a free period
			{
				Dates[no] = iterator;
				//cout<<"\n\tDEBUG : "<<iterator.get_day_as_int()<<endl;
				//cout<<"\n\t"<<iterator.get_day()<<" "<<iterator.get_date()<<endl; cin.get();
				no++;
			}
		}

		return no;
	}

	else if ( mode == 1 )
	{
		Date iterator;
		iterator.set_today();

		short unsigned int i;

		short unsigned int day;

		short unsigned int no = 0;

		for ( ; iterator<=to; ++iterator )
		{
			day = iterator.get_day_as_int();

			for ( i=no_of_periods-1; time_table[day][i]==0 && i>=0; i-- )
				{}

			if ( i == -1 || i == 0)
			{
				continue;
			}
			else if ( time_table[day][i] == subject_index+1 )
			{
				Dates[no] = iterator;
				//cout<<"\n\t"<<iterator.get_day()<<" "<<iterator.get_date()<<endl; cin.get();
				no++;
			}
		}

		return no;
	}

	else if ( mode == 2 )
	{
		Date iterator;
		iterator.set_today();

		short unsigned int i;

		short unsigned int day;

		short unsigned int no = 0;

		for ( ; iterator<=to; ++iterator )
		{
			day = iterator.get_day_as_int();

			for ( i=0; i<(no_of_periods-1); i++ )
			{
				if ( time_table[day][i]==0 && time_table[day][i+1]==subject_index+1)
				{
				Dates[no] = iterator;
				//cout<<"\n\t"<<iterator.get_day()<<" "<<iterator.get_date()<<endl; cin.get();
				no++;
				}
			}

		}

		return no;
	}

	else if ( mode == 3 )
	{
		Date iterator;
		iterator.set_today();

		short unsigned int i;

		short unsigned int day;

		short unsigned int no = 0;

		for ( ; iterator<=to; ++iterator )
		{
			day = iterator.get_day_as_int();

			for ( i=0; i<(no_of_periods-1); i++ )
			{
				if ( time_table[day][i]==subject_index+1 && time_table[day][i+1]==0 )
				{
				Dates[no] = iterator;
				//cout<<"\n\t"<<iterator.get_day()<<" "<<iterator.get_date()<<endl; cin.get();
				no++;
				}
			}

		}

		return no;
	}

}