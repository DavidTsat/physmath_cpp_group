#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <assert.h>
#include <iostream>
//#define debug

using namespace std;

struct migration_entry
{
	struct year_month_
	{
		uint16_t y;
		uint16_t m;

		friend ostream& operator<<(ostream& os, const year_month_& yy)
		{
			return os << yy.y << ':' << yy.m;
		}
	};
	enum passenger_type_
	{
		long_term_migrant, short_term_migrant
	};
	enum direction_
	{
		arrival, departure
	};
	enum sex_
	{
		male, female
	};
	struct age_
	{
		uint16_t l;
		uint16_t u;

		friend ostream& operator<<(ostream& os, const age_& yy)
		{
			return os << yy.l << ':' << yy.u;
		}
	};
	enum status_
	{
		final, provisional
	};
	
	static vector<string> header;

	year_month_ year_month;
	year_month_ month_of_release;
	passenger_type_ passenger_type;
	direction_ direction;
	sex_ sex;
	age_ age;
	uint16_t estimate;
	uint16_t standard_error;
	status_ status;
};

vector<string> migration_entry::header;

class parse_csv
{
	string csv_path = "D:/international-migration-march-2022-estimated-migration-by-age-sex.csv";

	migration_entry::year_month_ extract_date(const string& s) const
	{
		migration_entry::year_month_ r{};
		regex reg("\\d+", regex_constants::ECMAScript | regex_constants::icase);

		sregex_iterator r_begin(s.cbegin(), s.cend(), reg);
		sregex_iterator r_end = sregex_iterator();

		assert(distance(r_begin, r_end) == 2);

		r.y = atoi((*r_begin).str().c_str());
		r.m = atoi((*++r_begin).str().c_str());

		return r;
	}

	vector<string> extract_header(ifstream& fs) const
	{
		vector<string> header_entries;
		string header;

		getline(fs, header);
		regex r_header("\".*?\"", regex_constants::ECMAScript | regex_constants::icase);

		sregex_iterator r_begin(header.cbegin(), header.cend(), r_header);
		sregex_iterator r_end = sregex_iterator();

		while (r_begin != r_end)
		{
			const string& column_name = (*r_begin).str();

			header_entries.push_back(string(column_name.cbegin() + 1, column_name.cend() - 1));
			++r_begin;
		}
		return header_entries;
	}

	migration_entry::year_month_ extract_year_month(const string& s) const
	{
		return extract_date(s);
	}

	migration_entry::year_month_ extract_month_of_release(const string& s) const
	{
		return extract_date(s);
	}

	migration_entry::passenger_type_ extract_passenger_type(const string& s) const
	{
		migration_entry::passenger_type_ r{};
		regex reg_long("long[-_]?term migrant", regex_constants::ECMAScript | regex_constants::icase);
		regex reg_short("short[-_]?term migrant", regex_constants::ECMAScript | regex_constants::icase);

		if (regex_search(s, reg_long))
		{
			r = migration_entry::passenger_type_::long_term_migrant;
		}
		else if (regex_search(s, reg_short))
		{
			r = migration_entry::passenger_type_::short_term_migrant;
		}
		// todo - handle bad case
		return r;
	}
		
	migration_entry::direction_ extract_direction(const string& s) const
	{
		migration_entry::direction_ r{};
		regex reg_arriv("arrival", regex_constants::ECMAScript | regex_constants::icase);
		regex reg_depart("departure", regex_constants::ECMAScript | regex_constants::icase);

		if (regex_search(s, reg_arriv))
		{
			r = migration_entry::direction_::arrival;
		}
		else if (regex_search(s, reg_depart))
		{
			r = migration_entry::direction_::departure;
		}
		return r;
	}
			
	migration_entry::sex_ extract_sex(const string& s) const
	{
		migration_entry::sex_ r{};

		regex reg_male("\"male", regex_constants::ECMAScript | regex_constants::icase);
		regex reg_female("\"female", regex_constants::ECMAScript | regex_constants::icase);

		if (regex_search(s, reg_male))
		{
			r = migration_entry::sex_::male;
		}
		else if (regex_search(s, reg_female))
		{
			r = migration_entry::sex_::female;
		}
		return r;
	}
				
	migration_entry::age_ extract_age(const string& s) const
	{
		migration_entry::age_ r{};
		regex reg("\\d+", regex_constants::ECMAScript | regex_constants::icase);

		sregex_iterator reg_begin(s.cbegin(), s.cend(), reg);
		sregex_iterator reg_end = sregex_iterator();

		assert(distance(reg_begin, reg_end) == 2);

		r.l = atoi((*reg_begin).str().c_str());
		r.u = atoi((*++reg_begin).str().c_str());

		return r;
	}
				
	uint16_t extract_estimate(const string& s) const
	{
		regex reg("\\d+", regex_constants::ECMAScript | regex_constants::icase);

		sregex_iterator reg_begin(s.cbegin(), s.cend(), reg);
		sregex_iterator reg_end = sregex_iterator();

		assert(distance(reg_begin, reg_end) == 1);

		return atoi((*reg_begin).str().c_str());
	}
				
	uint16_t extract_standard_error(const string& s) const
	{
		regex reg("\\d+", regex_constants::ECMAScript | regex_constants::icase);

		sregex_iterator reg_begin(s.cbegin(), s.cend(), reg);
		sregex_iterator reg_end = sregex_iterator();

		assert(distance(reg_begin, reg_end) == 1);

		return atoi((*reg_begin).str().c_str());
	}
				
	migration_entry::status_ extract_status(const string& s) const
	{
		migration_entry::status_ r{};
		regex reg_final("\"final\"", regex_constants::ECMAScript | regex_constants::icase);
		regex reg_prov("\"provisional\"", regex_constants::ECMAScript | regex_constants::icase);

		if (regex_match(s, reg_final))
		{
			r = migration_entry::status_::final;
		}
		else if (regex_match(s, reg_prov))
		{
			r = migration_entry::status_::provisional;
		}

		return r;
	}

public:
	vector<migration_entry> parse() const
	{
		ifstream fs(csv_path);
		//todo handle error

		vector<string> header_line = extract_header(fs);

		migration_entry::header = header_line;

#ifdef debug
		//cout << "header: ";
		for (string& s : migration_entry::header)
		{
			cout << s << " ";
		}
		cout << endl;
#endif
		string line;
		vector<migration_entry> v;

#ifdef debug
		size_t line_num = 1;
#endif
		while (getline(fs, line))
		{
		//	cout << line << '\n';
			/*
			 parsing year_month and month_of_release
			*/
			regex r_line("(.*?,)|(\".*$)"); // split by ,
			sregex_iterator reg_begin(line.cbegin(), line.cend(), r_line);
			sregex_iterator reg_end = sregex_iterator();
			assert(distance(reg_begin, reg_end) == migration_entry::header.size());
#ifdef debug
			cout << "processing line Num " << line_num++ << endl;
#endif

			size_t i = 0;
			migration_entry mig_elem;
			while (reg_begin != reg_end)
			{
				const string& entry = (*reg_begin).str();
#ifdef debug
	//			cout << entry << '\n';
				cout << "extracting " + migration_entry::header[i] << '\n';
#endif
				switch (i)
				{
					case 0:
					{
						mig_elem.year_month = extract_year_month(entry);
						break;
					}
					case 1:
					{
						mig_elem.month_of_release = extract_month_of_release(entry);
						break;
					}
					case 2:
					{
						mig_elem.passenger_type = extract_passenger_type(entry);
						break;
					}
					case 3:
					{
						mig_elem.direction = extract_direction(entry);
						break;
					}
					case 4:
					{
						mig_elem.sex = extract_sex(entry);
						break;
					}
					case 5:
					{
						mig_elem.age = extract_age(entry);
						break;
					}
					case 6:
					{
						mig_elem.estimate = extract_estimate(entry);
						break;
					}
					case 7:
					{
						mig_elem.standard_error = extract_standard_error(entry);
						break;
					}
					case 8:
					{
						mig_elem.status = extract_status(entry);
						break;
					}
				}
				++reg_begin;
				++i;
			}
#ifdef debug
			cout << endl;
#endif
			v.push_back(mig_elem);
		}
		return v;
	}
};