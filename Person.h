#ifndef PERSON_H

	#define PERSON_H

	#include <string>

	using namespace std;

	class Person
	{
		protected:
			string name;
			string password;

		public:

			// Declaring Setters and Getters
			string get_name();
			void set_name(string);
			string get_password();
			void set_password(string);
			// Setters and Getters declared

			Person() : name(""), password("")
			{

			}

	};

#endif // PERSON_H
