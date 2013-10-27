#ifndef BUNKER_H

	#define BUNKER_H

	#include <vector>
	#include <iostream>
	#include "Person.h"
	#include "Date.h"


	class Bunker : public Person
	{
		private:

			short unsigned int no_of_subjects;
			short unsigned int no_of_periods;
			std::vector<std::string> subject_names;
			std::vector< std::vector<short unsigned int> > time_table;
			std::vector< std::vector<short unsigned int> > no_of_periods_per_day_per_subject;		//day 0 : monday; day 6 : sunday//Will not write this to file, will derive as read from file
			short unsigned int total_no_of_bunks;													//Will not write this to file, will derive as read from file
			float total_attendance;																	//Will not write this to file, will derive as read from file
			std::vector<short unsigned int> no_of_bunks_per_subject;
			std::vector< std::vector<Date> > date_of_bunk_per_subject_per_bunk;
			std::vector<float> attendance_per_subject;												//Will not write this to file, will derive as read from file
			std::vector<bool> free_days;
			std::vector<float> min_attendance_per_subject;
			float total_min_attendance;
			Date starting_date;


		public:

			Bunker() : Person(), no_of_subjects(0), no_of_periods(0), subject_names(25,""), time_table(7, std::vector<short unsigned int>(25,0)), no_of_periods_per_day_per_subject(7, std::vector<short unsigned int>(25,0)), total_no_of_bunks(0), total_attendance(0), no_of_bunks_per_subject(25,0), date_of_bunk_per_subject_per_bunk(25, std::vector<Date>(1000)), attendance_per_subject(25,0), free_days(7,false), min_attendance_per_subject(25,0), total_min_attendance(0)
			{

			}

			// Declaring Setters and Getters
			void set_no_of_subjects (short unsigned int);
			short unsigned int get_no_of_subjects (void);

			void set_no_of_periods (short unsigned int);
			short unsigned int get_no_of_periods (void);

			void set_subject_names (std::vector<std::string>);
			std::vector<std::string> get_subject_names (void);

			void set_time_table (std::vector< std::vector<short unsigned int> >);
			std::vector< std::vector<short unsigned int> > get_time_table (void);

			void set_total_no_of_bunks ( short unsigned int );
			short unsigned int get_total_no_of_bunks ( void );

			void set_total_attendance ( float );
			float get_total_attendance ( void );

			void set_no_of_bunks_per_subject (std::vector<short unsigned int>);
			std::vector<short unsigned int> get_no_of_bunks_per_subject (void);

			std::vector< std::vector<Date> > get_date_of_bunk_per_subject_per_bunk ( void );

			void set_attendance_per_subject (std::vector<float>);
			std::vector<float> get_attendance_per_subject (void);

			void set_free_days (std::vector<bool>);
			std::vector<bool> get_free_days (void);

			void set_min_attendance_per_subject ( std::vector<float> );
			std::vector<float> get_min_attendance_per_subject ( void );

			void set_total_min_attendance ( float );
			float get_total_min_attendance ( void );

			void set_starting_date ( Date );
			Date get_starting_date ( void );
			Date& obtain_starting_date ( void );
			// Setters and Getters declared

			//Declaration of File Handeling Methods : BEGIN
			void write_to_file (void);
			short unsigned int read_from_file (string);
			void write_to_file_at_position ( void );
			//Declaration of File Handeling Methods : END

			void calculate_total_no_of_bunks ( void );
			void register_bunk ( short unsigned int, Date);
			void calculate_attendance ( Date, Date );
			void calculate_no_of_periods_per_day_per_subject ( void );
			void calculate_no_of_bunks_in_date_range ( Date, Date );
			short unsigned int suggest_bunks ( short unsigned int, Date );
			short unsigned int suggest_bunks ( short unsigned int, Date, vector<Date>&,  short unsigned int );

	};

#endif // BUNKER_H
