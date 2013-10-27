#ifndef DATE_H

	#define DATE_H

	#include <string>
	#include <fstream>


	class Date
	{
		protected:

			std::string day;
			short unsigned int date, month, year;

		public:

			Date() : day(""), date(0), month(0), year(0)
			{

			}

			// Declaring Setters and Getters : BEGIN
			void set_date ( short unsigned int );
			void set_month ( short unsigned int );
			void set_year ( short unsigned int );

			short unsigned int get_date ( void );
			short unsigned int get_month ( void );
			short unsigned int get_year ( void );
			std::string get_day ( void );
			short unsigned int get_day_as_int ( void );
			// Declaring Setters and Getters : END

			void calc_day ( void );
			void sanitize ( tm& );
			void set_today ( void );
			void convert_to_structure ( tm& );
			void convert_from_structure ( tm );
			void write_to_file ( std::ofstream& );
			void read_from_file ( std::ifstream& );

			bool operator == ( Date );
			bool operator < ( Date );
			bool operator > ( Date );
			bool operator <= ( Date );
			bool operator >= ( Date );
			Date operator ++ ();

	};

#endif // DATE_H
