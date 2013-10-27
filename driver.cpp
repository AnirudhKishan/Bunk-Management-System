//**************************************************
//Header Files : BEGIN
#include <iostream>
#include <stdlib.h>
#include <limits>
#include <string>
#include <vector>
#include "Bunker.h"
//Header Files : END
//**************************************************

//**************************************************
using namespace std;
//**************************************************

//**************************************************
//Global Variables Declerations : BEGIN
string trash;		//Used to pause the screen
//Global Variables Declerations : END
//**************************************************

//**************************************************
//Global Function Declerations : BEGIN
void first_menu(void);
void login(void);		//if starting date is entered, logs in; else prompts for starting date
void dashboard ( Bunker& );
void register_bunk_interface ( Bunker& );
void analyse_attendance_interface ( Bunker );
void see_bunk_interface ( Bunker );
void suggest_bunks_interface ( Bunker );
void see_registered_details_interface ( string );
void register_new_user(void);
void read_free_days(vector<bool>&);
void read_min_attendance_per_subject ( vector<float>&, short unsigned int, vector<string>, float );
void fill_time_table ( vector< vector<short unsigned int> >&, vector<bool>&, short unsigned int, vector<string>, short unsigned int);
//Global Function Declerations : END
//**************************************************

//**************************************************
// main() Decleration and Definition : BEGIN
int main(void)
{
	first_menu();

	return 0;
}
// main() Decleration and Definition : END
//**************************************************

//**************************************************
//first_menu(void) Definition : BEGIN
void first_menu(void)
{

	short unsigned int choice;

	do
	{
		system("clear");

		cout<<"\t*Main Menu*\n\n";

		cout<<"What do you want to do? :-\n\n1. Login\n2. Register\n3. Exit\n\nChoice: ";
		if (!(cin >> choice))																		//Note: '\n' left behind in input stream
		{
			cout << "\n\n\t\tERROR : Please enter proper number only\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

		switch (choice)
		{
			case 1 :	login(); break;
			case 2 :	register_new_user(); break;

			case 3 :	break;

			default :	cout<<"\n\n\t\tWRONG CHOICE!!!\n\t\tPress Enter to Choose Again > ";
						getline(cin,trash);
		}
	} while (choice!=3);

	return;
}
//first_menu(void) Definition : END
//**************************************************

//**************************************************
//login(void) Definition : BEGIN
void login (void)
{

	short unsigned int flag, choice;
	string name;
	Bunker obj;

	//Reading the Name and Checking whether it exists in the database : BEGIN
	do
	{
		flag = 0;

		system("clear");
		cout<<"\n\n\t\tEnter Your Name : "; getline(cin,name);

		flag = obj.read_from_file(name);
		if (flag==0)
		{
			//Nothing to be done here
		}
		else if (flag==1)
		{
			cout<<"\n\n\t\tERROR : Call Program Maintaner ( Error Code "<<flag<<" )";
			getline(cin,trash);
			return;
		}
		else if (flag==2)
		{
			cout<<"\n\n\t\tERROR : Name Not Found\n\n\t\t";
			cout<<"*Press Enter* to continue > "; getline(cin,trash);
			return;
		}

	}while (0);
	//Reading the Name and Checking whether it exists in the database : END

	//Checking Password : Begin
	string pass;
	cout<<"\n\n\t\tEnter Password : ";
	getline ( cin, pass );

	if ( pass != obj.get_password() )
	{
		cout<<"\n\n\t\t\tWRONG PASSWORD!!!!";
		cout<<"\n\t\t\tPress Enter to Continue > ";	getline(cin,trash);
		return;
	}

	//Checking whether the Starting Date has been entered : BEGIN
	if ( obj.get_starting_date().get_month() == 0 )		//i.e. the Starting Date has not been entered
	{
		do
		{

			system("clear");
			cout<<"\n\n\t\tYou have not entered the Starting Date till now.";
			cout<<"\n\n\t\tYou need to enter your Starting Date of the Term before proceeding.";

			cout<<"\n\n\n\nWhat do you want to do? :-";
			cout<<"\n\n1. Enter the Starting Date of the Term\n2. Exit\n\nChoice : ";

			if (!(cin >> choice) || (choice!=1 && choice!=2))
			{
				cout << "\n\n\t\tERROR : Please enter proper Choice only\n\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				choice=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			}

			if (choice == 1)
			{
				short unsigned int date, month, year;

				cout<<"\n\n";
				cout<<"Enter the Starting Date of the Term (as Date/Month/Year):-\n";
				cout<<"\nDate : "; cin>>date; cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				cout<<"\nMonth : "; cin>>month; cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				cout<<"\nYear : "; cin>>year; cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

				obj.obtain_starting_date().set_date(date);
				obj.obtain_starting_date().set_month(month);
				obj.obtain_starting_date().set_year(year);
				obj.obtain_starting_date().calc_day();

				obj.write_to_file_at_position();

				cout<<"\n\n\n\t\tStarting Date Entered Successfully!!!";
				cout<<"\n\n\t\tPress Enter to Continue > "; getline(cin,trash);

				break;

			}

		}while(choice!=2);
	}
	//Checking whether the Starting Date has been entered : END

	//Redirecting to Dashboard
	dashboard(obj);

}
//login(void) Definition : END
//**************************************************

//**************************************************
//dashboard (Bunker) Definition : BEGIN
void dashboard (Bunker& B)
{
	short unsigned int choice;

	do
	{
		system("clear");
		cout<<"What do you want to do?:-\n\n";
		cout<<"1. Register a Bunk\n2. Analyse your attendance\n3. See your Bunks\n4. When to Bunk\n5. See your Registered Details\n6. Exit\n\nChoice : ";

		if (!(cin >> choice) && (choice<1 && choice>4) )
		{
			cout << "\n\n\t\tERROR : Please enter proper Choice only\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

		switch (choice)
		{
			case 1 :	register_bunk_interface(B);
						break;
			case 2 :	analyse_attendance_interface(B);
						break;
			case 3 :	see_bunk_interface(B);
						break;
			case 4 :	suggest_bunks_interface(B);
						break;
			case 5 :	see_registered_details_interface(B.get_name());
						break;
		}

	} while (choice!=6);
}
//dashboard (Bunker) Definition : END
//**************************************************

//**************************************************
//register_bunk_interface ( void ) Definition : BEGIN
void register_bunk_interface ( Bunker& B )
{
	system("clear");
	cout<<"Your Subject Codes and the Respective Subjects are :-\n\n";

	//printing a list of subjects : BEGIN
	short unsigned int i;
	short unsigned int no_of_subjects = B.get_no_of_subjects();
	vector<string> subject_names = B.get_subject_names();
	for (i=0; i<no_of_subjects; i++)
	{
		cout<<(i+1)<<". "<<subject_names[i]<<endl;
	}
	//printing a list of subjects : END

	//asking as to which subject the bunk needs to be registered in : BEGIN
	short unsigned int subject_number=0;		//a 0 subject number indicates that a proper subject code is yet to be entered
	do
	{
		cout<<"\n\nEnter the Subject Code in which you want to register a Bunk : ";
		if (!(cin >> subject_number) || (subject_number<1 || subject_number>no_of_subjects))
		{
			cout<<endl<<endl<<"\t\tERROR : Please enter proper Subject Code only";
			cout<<endl<<"\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			subject_number=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

	} while (subject_number==0);
	//asking as to which subject the bunk needs to be registered in : END

	//asking the bunk date : BEGIN
	short unsigned int choice=0;
	do
	{
		cout<<"\n\nWhen did the bunk take place?:-\n\n";
		cout<<"1. Today\n2. Specify Date\n\nChoice : ";
		if ( !(cin >> choice) || (choice!=1 && choice!=2) )
		{
			cout<<endl<<endl<<"\t\tERROR : Please enter proper Choice only";
			cout<<endl<<"\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

	} while (choice==0);

	Date date_of_bunk;

	switch (choice)
	{
		case 1 :	date_of_bunk.set_today();
					break;

		case 2 :	cout<<"\n\n\nEnter Date as ( Date / Month / Year ) :-";
					short unsigned int date, month, year;
					date = month = year = 0;
					do
					{
						cout<<"\n\nEnter Date : ";
						if ( !(cin >> date) || (date<1 || date>31) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Date only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							date=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (date==0);

					do
					{
						cout<<"\nEnter Month : ";
						if (!(cin >> month) || (month<1 || month>12) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Month only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							month=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (month==0);

					do
					{
						cout<<"\nEnter Year : ";
						if (!(cin >> year))
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Year only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							year=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (year==0);

					date_of_bunk.set_date(date);
					date_of_bunk.set_month(month);
					date_of_bunk.set_year(year);
					date_of_bunk.calc_day();
	}
	//asking the bunk date : END

	//Registering the Bunk : BEGIN
	B.register_bunk ( subject_number-1, date_of_bunk);
	//Registering the Bunk : END

	//Displaying current attendance standings : BEGIN
	B.read_from_file(B.get_name());

	float current_subject_min_attendance = B.get_min_attendance_per_subject()[subject_number-1];
	float total_min_attendance = B.get_total_min_attendance();
	float current_subject_no_of_bunks = B.get_no_of_bunks_per_subject()[subject_number-1];
	float current_subject_attendance = B.get_attendance_per_subject()[subject_number-1];
	float total_attendance = B.get_total_attendance();

	system("clear");
	cout<<"Number of Bunks in "<<subject_names[subject_number-1]<<" is : "<<current_subject_no_of_bunks;
	cout<<"\n\n\nAttendence in "<<subject_names[subject_number-1]<<" is : "<<current_subject_attendance<<" %";
	cout<<"\n\nTotal Attendance is : "<<total_attendance<<" %";

	cout<<"\n\nPress Enter to Continue > "; getline(cin,trash);


	system("clear");
	//Displaying warnings wrt Current Subject's Attendance : BEGIN
	if ( current_subject_attendance < current_subject_min_attendance )
	{
		cout<<"\n\n\t\tWARNNING : YOUR ATTENDANCE IN "<<subject_names[subject_number-1]<<" IS BELOW ITS MINIMUM";
		cout<<"\n\n\t\tIT IS STRONGLY ADVISED THAT YOU ANALYSE YOUR ATTENDANCE AND TAKE PROPER MEASURES";
		cout<<"\n\n\n\t\tPress Enter to Continue > "; getline(cin,trash);
	}
	else if ( (current_subject_attendance - (0.25*current_subject_attendance)) <= current_subject_min_attendance )
	{
		cout<<"\n\n\t\tWARNING : Your Attendance in "<<subject_names[subject_number-1]<<" is running low";
		cout<<"\n\n\t\tIt is advised that you do not bunk anymore.";
		cout<<"\n\n\n\t\tPress Enter to Continue > "; getline(cin,trash);
	}
	//Displaying warnings wrt Current Subject's Attendance : END

	//Displaying warnings wrt Total Attendance : BEGIN
	if ( total_attendance < total_min_attendance )
	{
		cout<<"\n\n\t\tWARNNING : YOUR TOTAL ATTENDANCE IS BELOW ITS MINIMUM";
		cout<<"\n\n\t\tIT IS STRONGLY ADVISED THAT YOU ANALYSE YOUR ATTENDANCE AND TAKE PROPER MEASURES";
		cout<<"\n\n\n\t\tPress Enter to Continue > "; getline(cin,trash);
	}
	else if ( (total_attendance - (0.25*total_attendance)) <= total_min_attendance )
	{
		cout<<"\n\n\t\tWARNING : Your Total Attendance is running low";
		cout<<"\n\n\t\tIt is advised that you do not bunk anymore.";
		cout<<"\n\n\n\t\tPress Enter to Continue > "; getline(cin,trash);
	}
	//Displaying warnings wrt Total Attendance : END

	//Displaying current attendance standings : END

	system("clear");
	cout<<"Your Bunk has been Registered Succesfully!";
	cout<<"\n\nPress Enter to Continue > "; getline(cin,trash);

}
//register_bunk_interface ( void ) Definition : END
//**************************************************

//**************************************************
//analyse_attendance_interface ( Bunker ) Definition : BEGIN
void analyse_attendance_interface ( Bunker B )		//INTEGRETY LOST
{
	short unsigned int choice = 0;

	do
	{
		system("clear");
		cout<<"From Which Date do you want to analyse your attendance?:-\n\n";
		cout<<"1. Starting Date\n2. Specify Date\n\nChoice : ";
		if ( !(cin >> choice) || (choice!=1 && choice!=2) )
		{
			cout<<endl<<endl<<"\t\tERROR : Please enter proper Choice only";
			cout<<endl<<"\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

	} while (choice==0);

	Date from;

	switch (choice)
	{
		case 1 :	from = B.get_starting_date();
					break;

		case 2 :	cout<<"\n\n\nEnter Date as ( Date / Month / Year ) :-";
					short unsigned int date, month, year;
					date = month = year = 0;

					do
					{
						cout<<"\n\nEnter Date : ";
						if ( !(cin >> date) || (date<1 || date>31) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Date only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							date=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (date==0);

					do
					{
						cout<<"\nEnter Month : ";
						if (!(cin >> month) || (month<1 || month>12) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Month only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							month=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (month==0);

					do
					{
						cout<<"\nEnter Year : ";
						if (!(cin >> year))
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Year only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							year=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (year==0);

					from.set_date(date);
					from.set_month(month);
					from.set_year(year);
					from.calc_day();

	}

	do
	{
		system("clear");
		cout<<"To Which Date do you want to analyse your attendance?:-\n\n";
		cout<<"1. Today\n2. Specify Date\n\nChoice : ";
		if ( !(cin >> choice) || (choice!=1 && choice!=2) )
		{
			cout<<endl<<endl<<"\t\tERROR : Please enter proper Choice only";
			cout<<endl<<"\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

	} while (choice==0);

	Date to;

	switch (choice)
	{
		case 1 :	to.set_today();
					break;

		case 2 :	cout<<"\n\n\nEnter Date as ( Date / Month / Year ) :-";
					short unsigned int date, month, year;
					date = month = year = 0;

					do
					{
						cout<<"\n\nEnter Date : ";
						if ( !(cin >> date) || (date<1 || date>31) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Date only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							date=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (date==0);

					do
					{
						cout<<"\nEnter Month : ";
						if (!(cin >> month) || (month<1 || month>12) )
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Month only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							month=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (month==0);

					do
					{
						cout<<"\nEnter Year : ";
						if (!(cin >> year))
						{
							cout<<endl<<endl<<"\t\tERROR : Please enter proper Year only";
							cout<<endl<<"\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							year=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
					} while (year==0);

					to.set_date(date);
					to.set_month(month);
					to.set_year(year);
					to.calc_day();

	}

	//calculating attendance as of now : BEGIN
	Date today;
	today.set_today();

	B.calculate_attendance ( B.get_starting_date(), today );
	//calculating attendance as of now : END

	short unsigned int no_of_subjects;
	no_of_subjects = B.get_no_of_subjects();
	int i;

	if ( from==B.get_starting_date() && to == today )
	{
		system("clear");
		cout<<"Your attendance is:-\n";
		for (i=0; i<no_of_subjects; i++)
		{
			cout<<B.get_subject_names()[i]<<" - "<<B.get_attendance_per_subject()[i]<<" %\n";
		}
	}
	else if ( to < today )
	{
		system("clear");
		cout<<"Your current attendance is:-\n";
		for (i=0; i<no_of_subjects; i++)
		{
			cout<<B.get_subject_names()[i]<<" - "<<B.get_attendance_per_subject()[i]<<" %\n";
		}

		cout<<"\n\nYour attendance till "<<to.get_date()<<" / "<<to.get_month()<<" / "<<to.get_year()<<" is:-\n";
		B.calculate_attendance ( from, to );
		for (i=0; i<no_of_subjects; i++)
		{
			cout<<B.get_subject_names()[i]<<" - "<<B.get_attendance_per_subject()[i]<<" %\n";
		}
	}
	else
	{
		//Printing the attendance as of now : BEGIN
		system("clear");
		cout<<"If your attendance followes its usual path, your attendance would be like :- \n";
		B.calculate_attendance ( from, today );
		for (i=0; i<no_of_subjects; i++)
		{
			cout<<B.get_subject_names()[i]<<" - "<<B.get_attendance_per_subject()[i]<<" %\n";
		}
		//Printing the attendance as of now : END

		//calculating & printing attendance assuming that no bunk from now : BEGIN
		B.calculate_attendance ( from , to );
		cout<<"\n\nIf you make no more bunks, your attendence till "<<to.get_date()<<" / "<<to.get_month()<<" / "<<to.get_year()<<" would be:-\n";
		for (i=0; i<no_of_subjects; i++)
		{
			cout<<B.get_subject_names()[i]<<" - "<<B.get_attendance_per_subject()[i]<<" %\n";
		}
		//calculating & printing attendance assuming that no bunk from now : END
	}

	printf("\n\nPress Enter to Continue > ");
	getline(cin,trash);

}
//analyse_attendance_interface ( Bunker ) Definition : END
//**************************************************

//**************************************************
//see_bunk_interface ( Bunker ) Definition : BEGIN
void see_bunk_interface ( Bunker B )
{
	system("clear");

	short unsigned int i, j;

	short unsigned int no_of_subjects = B.get_no_of_subjects();
	vector<string> subject_names(no_of_subjects);
	subject_names = B.get_subject_names();
	vector<short unsigned int> no_of_bunks_per_subject(no_of_subjects);
	no_of_bunks_per_subject = B.get_no_of_bunks_per_subject();
	vector< vector<Date> > date_of_bunk_per_subject_per_bunk;
	date_of_bunk_per_subject_per_bunk = B.get_date_of_bunk_per_subject_per_bunk();

	for ( i=0; i<no_of_subjects; i++)
	{
		cout<<"For *"<<subject_names[i]<<"*:-\n";
		for ( j=0; j<no_of_bunks_per_subject[i]; j++)
		{
			cout<<"\t\t"<<(j+1)<<". "<<date_of_bunk_per_subject_per_bunk[i][j].get_date()<<"/"<<date_of_bunk_per_subject_per_bunk[i][j].get_month()<<"/"<<date_of_bunk_per_subject_per_bunk[i][j].get_year()<<endl;
		}
		cout<<"\n\n";
	}

	cout<<"\n\n\nPress Enter to Continue > "; getline(cin,trash);
}
//see_bunk_interface ( Bunker ) Definition : END
//**************************************************

//**************************************************
//suggest_bunk_interface ( Bunker ) Definition : BEGIN
void suggest_bunks_interface ( Bunker B )
{
	int i;

	//getting subject and date : BEGIN
	short unsigned int subject_index;
	short unsigned int date, month, year;
	{
		short unsigned int no_of_subjects = B.get_no_of_subjects();
		vector<string> subject_names = B.get_subject_names();

		do
		{
			system("clear");
			for ( i=0; i<no_of_subjects; i++ )
			{
				cout<<(i+1)<<". "<<subject_names[i]<<endl;
			}

			cout<<"\n\nEnter the Subject Code : ";
			if ( !(cin >> subject_index) || ( subject_index>(no_of_subjects+1) ) )
			{
				cout<<endl<<endl<<"\t\tERROR : Please enter proper Subject Code only";
				cout<<endl<<"\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				subject_index=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				subject_index--;
				break;
			}

		} while (1);

		do
		{
			system("clear");

			cout<<"Enter the Date to which you want to get the suggested bunks ( as Date/Month/Year ) :-\n\n";

			cout<<"Date : ";
			if (!(cin >> date) || (date>31) )
			{
				cout<<endl<<endl<<"\t\tERROR : Please enter proper Date only";
				cout<<endl<<"\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				date=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			}

			cout<<"\nMonth : ";
			if (!(cin >> month) || (month>12) )
			{
				cout<<endl<<endl<<"\t\tERROR : Please enter proper Month only";
				cout<<endl<<"\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				month=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			}

			cout<<"\nYear : ";
			if (!(cin >> year))
			{
				cout<<endl<<endl<<"\t\tERROR : Please enter proper Year only";
				cout<<endl<<"\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				year=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				break;
			}

		} while (1);

	}
	//getting subject and date : END

	//setting 'to' date : BEGIN
	Date to;

	to.set_date(date);
	to.set_month(month);
	to.set_year(year);
	to.calc_day();
	//setting 'to' date : END


	short unsigned int no_of_bunks;

	vector<short unsigned int> periods (100, 0);
	vector<Date> Dates(100);

	no_of_bunks	= B.suggest_bunks( subject_index, to );
	system("clear");
	cout<<"You can have a total of *"<<no_of_bunks<<"* bunks";

	if ( no_of_bunks != 0)
	{
		{
			no_of_bunks = B.suggest_bunks ( subject_index, to, Dates, 0 );

			if ( no_of_bunks == 0)
			{
				cout<<"\n\n\t\tNo Bunks at the start of a day!";
			}
			else
			{
				cout<<"\n\nBunks at Start of Day:-\n";

				for ( i=0; i<no_of_bunks; i++)
				{
					cout<<"\n\t- "<<Dates[i].get_day()<<" : "<<Dates[i].get_date()<<"/"<<Dates[i].get_month()<<"/"<<Dates[i].get_year();
				}
			}

		}

		{
			no_of_bunks = B.suggest_bunks ( subject_index, to, Dates, 1 );

			if ( no_of_bunks == 0)
			{
				cout<<"\n\n\t\tNo Bunks at the end of a day!";
			}
			else
			{
				cout<<"\n\nBunks at End of Day:-\n";

				for ( i=0; i<no_of_bunks; i++)
				{
					cout<<"\n\t- "<<Dates[i].get_day()<<" : "<<Dates[i].get_date()<<"/"<<Dates[i].get_month()<<"/"<<Dates[i].get_year();
				}
			}
		}

		{
			no_of_bunks = B.suggest_bunks ( subject_index, to, Dates, 2 );

			if ( no_of_bunks == 0)
			{
				cout<<"\n\n\t\tNo Bunks with a free period before!";
			}
			else
			{
				cout<<"\n\nBunks with a free period before:-\n";

				for ( i=0; i<no_of_bunks; i++)
				{
					cout<<"\n\t- "<<Dates[i].get_day()<<" : "<<Dates[i].get_date()<<"/"<<Dates[i].get_month()<<"/"<<Dates[i].get_year();
				}
			}
		}

		{
			no_of_bunks = B.suggest_bunks ( subject_index, to, Dates, 3 );

			if ( no_of_bunks == 0)
			{
				cout<<"\n\n\t\tNo Bunks with a free period after!";
			}
			else
			{
				cout<<"\n\nBunks with a free period after:-\n";

				for ( i=0; i<no_of_bunks; i++)
				{
					cout<<"\n\t- "<<Dates[i].get_day()<<" : "<<Dates[i].get_date()<<"/"<<Dates[i].get_month()<<"/"<<Dates[i].get_year();
				}
			}
		}

	}

getline(cin,trash);

}
////suggest_bunk_interface ( Bunker ) Definition : END
//**************************************************

//**************************************************
//see_registered_details_interface ( string ) Definition : BEGIN
void see_registered_details_interface ( string name )
{
	//Showing Registered Information : BEGIN
	system("clear");
	cout<<"\tSuccessfully Registered New User\n\n";
	cout<<"New User details:-\n";

	Bunker check_bunker;
	short unsigned int flag;
	flag = check_bunker.read_from_file(name);
	if (flag!=0)
	{
		cout<<"\n\n\t\tERROR : Call Program Maintaner ( Error Code "<<flag<<" )";
		getline(cin,trash);
		return;
	}

	cout<<"Name : "<<check_bunker.get_name()<<endl;
	cout<<"Number of Subjects : "<<check_bunker.get_no_of_subjects()<<"\n";
	int i, j, k, l;
	for (i=0; i<check_bunker.get_no_of_subjects(); i++)
	{
		cout<<"\nSubject 1 : "<<(check_bunker.get_subject_names())[i];
	}
	cout<<"\n\nTime Table:-\n";
	//printing the current status of the time table
	{
		for (k=0; k<16; k++)
				cout<<"_";
		for (k=0; k<check_bunker.get_no_of_periods(); k++)
		{
			for (l=0; l<8; l++)
				cout<<"_";
		}
		cout<<endl;
		for (j=0; j<7; j++)
		{
			switch (j)
			{
				case 0 :	cout<<"Monday\t"; break;
				case 1 :	cout<<"Tuesday\t"; break;
				case 2 :	cout<<"Wednesday"; break;
				case 3 :	cout<<"Thursday"; break;
				case 4 :	cout<<"Friday\t"; break;
				case 5 :	cout<<"Saturday"; break;
				case 6 :	cout<<"Sunday\t"; break;
			}
			cout<<"\t| ";

			for (k=0; k<check_bunker.get_no_of_periods(); k++)
			{
				cout<<(check_bunker.get_time_table())[j][k]<<"\t| ";
			}

			cout<<endl;

			for (k=0; k<16; k++)
				cout<<"_";
			for (k=0; k<check_bunker.get_no_of_periods(); k++)
			{
				for (l=0; l<8; l++)
					cout<<"_";
			}
			cout<<endl;
		}
	}
	//printed the current status of the time table

	//Printing Minimum Attendances : BEGIN
	cout<<"\n\nTotal Minimum Attendance : "<<check_bunker.get_total_min_attendance()<<" %";

	cout<<"\n\nMinimum Attendence per Subject:-\n";
	for (i=0; i<check_bunker.get_no_of_subjects(); i++)
	{
		cout<<"\n"<<(i+1)<<". "<<( check_bunker.get_subject_names() )[i]<<"\t:\t"<<( check_bunker.get_min_attendance_per_subject() )[i]<<" %";
	}
	//Printing Minimum Attendances : END

	cout<<"\n\nPress Enter to Continue > ";
	getline(cin,trash);
	//Showing Registered Information : END
}
////see_registered_details_interface ( string ) Definition : END
//**************************************************

//**************************************************
//register_new_user(void) Definition : BEGIN
void register_new_user (void)
{
	short unsigned int i, j, k, l, flag;
	short unsigned int choice;

	//attributes of Person
	string name, password;

	//attributes of Bunker
	short unsigned int no_of_subjects;
	short unsigned int no_of_periods;
	vector<string> subject_names(25,"");
	vector< vector<short unsigned int> > time_table(7, vector<short unsigned int>(25,0));
	vector<short unsigned int> no_of_bunks_per_subject(25,0);
	//vector<float> attendance_per_subject(25,0);		//Not Needed while registering a New User
	vector<bool> free_days(7,false);
	float total_min_attendance;
	vector<float> min_attendance_per_subject(25,0);
/*
			name = "prakhar";
			password = "ani";
			no_of_subjects = 3;
			subject_names[0] = "fun"; subject_names[1] = "masti"; subject_names[2] = "emo";
			no_of_periods = 3;
			time_table[0][0] = 1; time_table[0][1] = 2; time_table[0][2] = 3;
			time_table[2][0] = 3; time_table[2][1] = 0; time_table[2][2] = 2;
*/
		free_days[5]=true; free_days[6]=true;

	//Reading Attributes : Begin

	do
	{
		do
		{
			Bunker obj_temp;

			system("clear");
			cout<<"Welcome, to New User Registeration";
			cout<<"\n\n\nEnter your name : ";
			getline(cin, name);
			if (name == "<!--start--!>")		//"<!--start--!>" indicates the start of a new object in the datafile
			{
				cout<<"\n\n\t\tERROR : *Invalid Name*, Press Enter to input again : ";
				getline(cin,trash);
				continue;
			}
			else if ( obj_temp.read_from_file(name) == 0 )
			{
				cout<<"\n\n\t\tERROR : Name already taken. Please choose a new name or contact the program maintainer";
				cout<<"\n\n\t\tPress Enter to input again : ";
				getline(cin,trash);
				continue;
			}
			else
			{
				break;
			}
		}while(1);


		while (1)
		{
			cout<<"\nHow many Subjects do you have?: ";
			if (!(cin >> no_of_subjects))
			{
				cout << "\n\n\t\tERROR : Please enter proper number only\n\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				choice=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			}

			break;
		}
		cout<<endl;

		for(i=0; i<no_of_subjects; i++)
		{
			do
			{
				cout<<"\nEnter the Name for Subject Number "<<i+1<<" : ";
				getline(cin, subject_names[i]);
				if (subject_names[i] == "<!--start--!>")		//"<!--start--!>" indicates the start of a new object in the datafile
				{
					cout<<"\n\n\t\tERROR : *Invalid Subject Name*, Press Enter to input again : ";
					getline(cin,trash);
					continue;
				}
				else
				{
					break;
				}
			}while(1);

		}

		//Checking if the attributes entered are correct
		do
		{
			system("clear");

			cout<<"As of now, we have the following information:-\n\n";
			cout<<"Name : "<<name<<endl;
			cout<<"Number of Subjects : "<<no_of_subjects<<"\n";

			for (i=0; i<no_of_subjects; i++)
			{
				cout<<"\nSubject 1 : "<<subject_names[i];
			}

			cout<<"\n\nIs this information correct? :-\n\n";
			cout<<"1. This information is correct, I'd like to continue with the registration process.\n";
			cout<<"2. I would like to re-enter the information.\n";
			cout<<"\nChoice : ";
			if (!(cin >> choice) || (choice!=1 && choice!=2) )
			{
				cout << "\n\n\t\tERROR : Please enter proper Choice\n\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				choice=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

		}while (choice!=1 && choice!=2);
		system("clear");
	} while (choice!=1);

	//Reading Free Days : BEGIN
	system("clear");
	cout<<"Now, Please tell us which of your days are Free / Working Days.\n\n";
	cout<<"Press Enter to Start : "; getline(cin,trash);
	read_free_days (free_days);
	//Reading Free Days : END

	//Reading Attributes : END

	//Reading Time Table : BEGIN
	system("clear");
	cout<<"Now, we have enough information to start filling up your Time Table\n\n";
	cout<<"Press Enter to Start : "; getline(cin,trash);
	do
	{
		system("clear");
		cout<<"How many Slots/Periods do you have in a day? : ";
		if (!(cin >> no_of_periods))
		{
			cout << "\n\n\t\tERROR : Please enter proper Number only\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); break;
		}
	}while(1);
	fill_time_table (time_table, free_days, no_of_subjects, subject_names, no_of_periods);
	system("clear");
	cout<<"\t\tGot the Time Table Successfully!!!";
	cout<<"\n\nPress Enter to Continue : "; getline(cin,trash);
	//Reading Time Table : END

	//Reading Total Minimum attendance : END
	do
	{
		system("clear");
		cout<<"Enter the Total Minimum attendance (in %) : ";
		if (!(cin >> total_min_attendance))
		{
			cout << "\n\n\t\tERROR : Please enter proper Number only\n\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			total_min_attendance=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

		cout<<"\n\nThe Total Minimum attendance has been entered as : "<<total_min_attendance<<" %";
		cout<<"\n\nWhat do you want to do?:-\n\n1. Continue\n2. Re-enter Total Minimum attendance\n\nChoice : ";
		if ( !(cin >> choice) || !(choice==1 || choice==2) )
		{
			cout << "\n\n\t\tERROR : Please enter proper Choice only\n\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

	} while (choice!=1);
	//Reading Total Minimum attendance : END

	//Reading Minimum attendance Per Subject : BEGIN
	system("clear");
	cout<<"Press Enter to Enter Minimum Attendence for Each Subject > "; getline(cin,trash);

	read_min_attendance_per_subject ( min_attendance_per_subject, no_of_subjects, subject_names, total_min_attendance );
	//Reading Minimum attendance Per Subject : END

	//Reading Password : BEGIN
	string password_temp;
	do
	{
		system("clear");
		cout<<"\n\n\t\t***Enter Password***\t\t: ";
		getline(cin, password);
		if (password == "<!--start--!>")		//"<!--start--!>" indicates the start of a new object in the datafile
		{
			cout<<"\n\n\t\tERROR : *Invalid Password*, Press Enter to input again : ";
			getline(cin,trash);
			continue;
		}
		cout<<"\n\n\t\t***Enter Password Again***\t: ";
		getline(cin,password_temp);

		if (password == password_temp)
		{
			break;
		}
		else
		{
			cout<<"\n\n\t\tERROR : Passwords do not Match!!!\n";
			cout<<"\n\t\tPress Enter to Input Again : "; getline(cin,trash);
			continue;
		}
	}while(1);

	cout<<"\n\n\t\tPassword Entered Successfully!!!\n";
	cout<<"\nPress Enter to Continue : "; getline(cin,trash);
	//Reading Password : END

	//Writing to Data File : BEGIN
	Bunker  new_bunker;

	new_bunker.set_name (name);
	new_bunker.set_password (password);
	new_bunker.set_no_of_subjects (no_of_subjects);
	new_bunker.set_no_of_periods (no_of_periods);
	new_bunker.set_subject_names (subject_names);
	new_bunker.set_time_table (time_table);
	new_bunker.set_free_days (free_days);
	new_bunker.set_min_attendance_per_subject ( min_attendance_per_subject );
	new_bunker.set_total_min_attendance (total_min_attendance);

	//calculating and filling no_of_periods_per_day_per_subject : BEGIN
	new_bunker.calculate_no_of_periods_per_day_per_subject();
	//calculating and filling no_of_periods_per_day_per_subject : END

	new_bunker.write_to_file();
	//Writing to Data File : END

	//Showing Registered Information : BEGIN
	system("clear");
	cout<<"\tSuccessfully Registered New User\n\n";
	cout<<"New User details:-\n";

	Bunker check_bunker;
	flag = check_bunker.read_from_file(name);
	if (flag!=0)
	{
		cout<<"\n\n\t\tERROR : Call Program Maintaner ( Error Code "<<flag<<" )";
		getline(cin,trash);
		return;
	}

	cout<<"Name : "<<check_bunker.get_name()<<endl;
	cout<<"Number of Subjects : "<<check_bunker.get_no_of_subjects()<<"\n";
	for (i=0; i<check_bunker.get_no_of_subjects(); i++)
	{
		cout<<"\nSubject 1 : "<<(check_bunker.get_subject_names())[i];
	}
	cout<<"\n\nTime Table:-\n";
	//printing the current status of the time table
	{
		for (k=0; k<16; k++)
				cout<<"_";
		for (k=0; k<check_bunker.get_no_of_periods(); k++)
		{
			for (l=0; l<8; l++)
				cout<<"_";
		}
		cout<<endl;
		for (j=0; j<7; j++)
		{
			switch (j)
			{
				case 0 :	cout<<"Monday\t"; break;
				case 1 :	cout<<"Tuesday\t"; break;
				case 2 :	cout<<"Wednesday"; break;
				case 3 :	cout<<"Thursday"; break;
				case 4 :	cout<<"Friday\t"; break;
				case 5 :	cout<<"Saturday"; break;
				case 6 :	cout<<"Sunday\t"; break;
			}
			cout<<"\t| ";

			for (k=0; k<check_bunker.get_no_of_periods(); k++)
			{
				cout<<(check_bunker.get_time_table())[j][k]<<"\t| ";
			}

			cout<<endl;

			for (k=0; k<16; k++)
				cout<<"_";
			for (k=0; k<check_bunker.get_no_of_periods(); k++)
			{
				for (l=0; l<8; l++)
					cout<<"_";
			}
			cout<<endl;
		}
	}
	//printed the current status of the time table

	//Printing Minimum Attendances : BEGIN
	cout<<"\n\nTotal Minimum Attendance : "<<check_bunker.get_total_min_attendance()<<" %";

	cout<<"\n\nMinimum Attendence per Subject:-\n";
	for (i=0; i<check_bunker.get_no_of_subjects(); i++)
	{
		cout<<"\n"<<(i+1)<<". "<<( check_bunker.get_subject_names() )[i]<<"\t:\t"<<( check_bunker.get_min_attendance_per_subject() )[i]<<" %";
	}
	//Printing Minimum Attendances : END

	cout<<"\n\nPress Enter to Continue > ";
	getline(cin,trash);
	//Showing Registered Information : END

}
//register_new_user(void) Definition : END
//**************************************************

//**************************************************
//read_free_days(vector<bool>&) Definition : BEGIN
void read_free_days ( vector<bool>& free_days )
{
	short unsigned int i, choice;
	do
	{
		system("clear");
		cout<<"\t\t_Please Select your Free/Non-Working Days_";
		cout<<"\n\nCurrent Status:-";

		//Show the Current Status
		for (i=0; i<7; i++)
		{
			cout<<endl;
			switch (i)
			{
				case 0 :	cout<<"Monday\t"; break;
				case 1 :	cout<<"Tuesday\t"; break;
				case 2 :	cout<<"Wednesday"; break;
				case 3 :	cout<<"Thursday"; break;
				case 4 :	cout<<"Friday\t"; break;
				case 5 :	cout<<"Saturday"; break;
				case 6 :	cout<<"Sunday\t"; break;
			}

			cout<<"\t->\t";

			if (free_days[i])
				cout<<"Free Day";
			else
				cout<<"Working Day";
		}
		//Current Status Shown

		cout<<"\n\n\n";

		//Showing the Menu for changing the current status
		for (i=0; i<7; i++)
		{
			cout<<"\n"<<i+1<<". Set ";

			switch (i)
			{
				case 0 :	cout<<"Monday\t"; break;
				case 1 :	cout<<"Tuesday\t"; break;
				case 2 :	cout<<"Wednesday"; break;
				case 3 :	cout<<"Thursday\t"; break;
				case 4 :	cout<<"Friday\t"; break;
				case 5 :	cout<<"Saturday\t"; break;
				case 6 :	cout<<"Sunday\t"; break;
			}

			cout<<"\tas\t";

			if (free_days[i])
				cout<<"Working Day";
			else
				cout<<"Free Day";
		}
		//Shown the Menu for changing the current status

		cout<<"\n\n\n8. Save and Continue";

		cout<<"\n\nChoice : ";
		if (!(cin >> choice))
		{
			cout << "\n\n\t\tERROR : Please enter proper Choice only\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (choice>8 || choice<1)
		{
			cout<<"\n\n\t\tERROR!!!\n\t\t\tWrong Input; Press Enter to Continue";
			getline(cin,trash);
			continue;
		}
		else if (choice<8)
		{
			free_days[choice-1] = !free_days[choice-1];
		}

	} while(choice!=8);
}
//**************************************************
//read_free_days(vector<bool>&) Definition : END

//**************************************************
//read_min_attendance_per_subject ( vector<short unsigned int>, short unsigned int ) Definition : BEGIN
void read_min_attendance_per_subject ( vector<float>& min_attendance_per_subject, short unsigned int no_of_subjects, vector<string> subject_names, float total_min_attendance)
{
	short unsigned int i, choice, subject_no;
	float attendance;

	//Assigning the Total Minimum attendance to each of the Minimum attendance per Subject : BEGIN
	for (i=0; i<no_of_subjects; i++)
	{
		min_attendance_per_subject[i] = total_min_attendance;
	}
	//Assigning the Total Minimum attendance to each of the Minimum attendance per Subject : END

	//Asking for and making changes to the Minimum attendance per Subject : BEGIN
	do
	{
		system("clear");

		cout<<"Current state of Minimum attendance per Subject:-\n\n";

		for (i=0; i<no_of_subjects; i++)
		{
			cout<<(i+1)<<". "<<subject_names[i]<<" : "<<min_attendance_per_subject[i]<<" %"<<endl;
		}

		cout<<"\n\nWhat do you want to do?:-\n\n";
		cout<<"1. Continue\n2. Change a Value\n\nChoice : ";
		if (!(cin >> choice) || (choice!=1 && choice!=2) )
		{
			cout << "\n\n\t\tERROR : Please enter proper Choice only\n\n\t\tPress Enter to Choose Again > ";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
			choice=0; continue;
		}
		else
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}

		switch (choice)
		{
			case 2 :	cout<<"\n\nEnter the Subject Number do you want to change : ";
						if ( !(cin >> subject_no) || (subject_no<1 || subject_no>no_of_subjects) )
						{
							cout << "\n\n\t\tERROR : Please enter proper Subject Number only\n\n\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							subject_no=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
						cout<<"\n\nEnter the Minimum attendance for "<<subject_names[subject_no-1]<<" (in %) : ";
						if (!(cin >> attendance))
						{
							cout << "\n\n\t\tERROR : Please enter proper Number only\n\n\t\tPress Enter to Choose Again > ";
							cin.clear();
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
							attendance=0; continue;
						}
						else
						{
							cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
						}
						min_attendance_per_subject[subject_no-1] = attendance;
						cout<<"\n\n\tMinimum attendance for "<<subject_names[subject_no-1]<<" has been set as : "<<min_attendance_per_subject[subject_no-1]<<" %";
						cout<<"\n\nPress Enter to Continue > "; getline(cin,trash);
						break;

			case 1 :	break;

			default :	cout<<"\n\n\tWRONG CHOICE\n\tPress Enter to Choose Again > ";
						getline(cin,trash);
		}

	} while (choice!=1);
	//Asking for and making changes to the Minimum attendance per Subject : END
}
//read_min_attendance_per_subject ( vector<short unsigned int>, short unsigned int ) Definition : END
//**************************************************

//**************************************************
//fill_time_table ( vector< vector<short unsigned int> >&, vector<bool>&, short unsigned int, vector<string>, short unsigned int) Definition : BEGIN
void fill_time_table ( vector< vector<short unsigned int> >& time_table, vector<bool>& free_days, short unsigned int no_of_subjects, vector<string> subject_names, short unsigned int no_of_periods)
{
	short unsigned int i, j, k, l, choice;

	do
	{
		//Getting the time table
		for (i=0; i<7; i++)
		{
			if (free_days[i]!=true)
			{

				//printing the current status of the time table
				{
					system("clear");
					if (i!=0)
						cout<<"Current Status of Time Table:-\n";

					for (k=0; k<16; k++)
							cout<<"_";
					for (k=0; k<no_of_periods; k++)
					{
						for (l=0; l<8; l++)
							cout<<"_";
					}
					cout<<endl;
					for (j=0; j<i; j++)
					{
						switch (j)
						{
							case 0 :	cout<<"Monday\t"; break;
							case 1 :	cout<<"Tuesday\t"; break;
							case 2 :	cout<<"Wednesday"; break;
							case 3 :	cout<<"Thursday"; break;
							case 4 :	cout<<"Friday\t"; break;
							case 5 :	cout<<"Saturday"; break;
							case 6 :	cout<<"Sunday\t"; break;
						}
						cout<<"\t| ";

						for (k=0; k<no_of_periods; k++)
						{
							cout<<time_table[j][k]<<"\t| ";
						}

						cout<<endl;

						for (k=0; k<16; k++)
							cout<<"_";
						for (k=0; k<no_of_periods; k++)
						{
							for (l=0; l<8; l++)
								cout<<"_";
						}
						cout<<endl;
					}
				}
				//printed the current status of the time table

				cout<<"\n0 -> Code for Free Period";
				for (j=0; j<no_of_subjects; j++)
				{
					cout<<"\n"<<j+1<<" -> Subject Code for ";
					cout<<subject_names[j];
				}

				cout<<"\n\nEnter the ";
				switch (i)
				{
					case 0 :	cout<<"Monday"; break;
					case 1 :	cout<<"Tuesday"; break;
					case 2 :	cout<<"Wednesday"; break;
					case 3 :	cout<<"Thursday"; break;
					case 4 :	cout<<"Friday"; break;
					case 5 :	cout<<"Saturday"; break;
					case 6 :	cout<<"Sunday"; break;
				}
				cout<<"'s Time Table:-\n\n";

				for (j=0; j<no_of_periods; j++)
				{
					cout<<"Period Number "<<j+1<<" (Enter Subject Code) : ";
					if (!(cin >> time_table[i][j]))
					{
						cout << "\n\n\t\tERROR : Please enter proper Subject Code only\n\t\tPress Enter to Choose Again > ";
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
						j--; continue;
					}
					else
					{
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}

					//Checking whether the Number Entered is a Valid Subject code
					for (k=0; k<=no_of_subjects; k++)
					{
						if (time_table[i][j] == k)
							break;
					}
					if (k==no_of_subjects+1)
					{
						cout << "\n\n\t\tERROR : Please enter proper Subject Code only\n\t\tPress Enter to Choose Again > ";
						getline(cin,trash); cout<<endl;
						j--; continue;
					}
					//Checked whether the Number Entered is a Valid Subject code

				}
			}
		}
		//Got the time table

		//asking for conformatin
		do
		{
			//printing the current status of the time table
			{
				system("clear");
				if (i!=0)
					cout<<"Current Status of Time Table:-\n";

				for (k=0; k<16; k++)
						cout<<"_";
				for (k=0; k<no_of_periods; k++)
				{
					for (l=0; l<8; l++)
						cout<<"_";
				}
				cout<<endl;
				for (j=0; j<i; j++)
				{
					switch (j)
					{
						case 0 :	cout<<"Monday\t"; break;
						case 1 :	cout<<"Tuesday\t"; break;
						case 2 :	cout<<"Wednesday"; break;
						case 3 :	cout<<"Thursday"; break;
						case 4 :	cout<<"Friday\t"; break;
						case 5 :	cout<<"Saturday"; break;
						case 6 :	cout<<"Sunday\t"; break;
					}
					cout<<"\t| ";

					for (k=0; k<no_of_periods; k++)
					{
						cout<<time_table[j][k]<<"\t| ";
					}

					cout<<endl;

					for (k=0; k<16; k++)
						cout<<"_";
					for (k=0; k<no_of_periods; k++)
					{
						for (l=0; l<8; l++)
							cout<<"_";
					}
					cout<<endl;
				}
			}
			//printed the current status of the time table

			cout<<"\n\nIs this information correct? :-\n\n";
			cout<<"1. This information is correct, I'd like to continue with the registration process.\n";
			cout<<"2. I would like to re-enter the information.\n";
			cout<<"\nChoice : ";
			if (!(cin >> choice) || (choice!=1 && choice!=2) )
			{
				cout << "\n\n\t\tERROR : Please enter proper Choice\n\t\tPress Enter to Choose Again > ";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); getline(cin,trash);
				choice=0; continue;
			}
			else
			{
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

		}while (choice!=1 && choice!=2);

	}while(choice!=1);
}
//fill_time_table ( vector< vector<short unsigned int> >&, vector<bool>&, short unsigned int, vector<string>) Definition : END
//**************************************************
