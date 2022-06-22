#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

void f1()
{
//	const char* vs char[]
	const char* c = "abcdefg";
	char cc[8] = "menkdfd";

	cout << sizeof(c) << " : " << strlen(c) << endl;
	cout << sizeof(cc) << " : " << strlen(cc) << endl;

}

void f2()
{
	/*
	char text[]{ "hello" };
	std::string str{ text };
	std::string more{ str };
	*/
	std::string_view text{ "hello" }; // представление для строки "hello", которое хранится в бинарном виде
	std::string_view str{ text }; // представление этой же строки - "hello"
	std::string_view more{ str };
}

void f3()
{
	std::string_view str{ "Trains are fast!" };

	std::cout << str.length() << '\n'; // 16
	std::cout << str.substr(0, str.find(' ')) << '\n'; // Trains
	std::cout << (str == "Trains are fast!") << '\n'; // 1

	// Начиная с C++20
	std::cout << str.starts_with("Boats") << '\n'; // 0
	std::cout << str.ends_with("fast!") << '\n'; // 1

	std::cout << str << '\n'; // Trains are fast!
}

string_view f4_()
{
	string ss = "abcdef";
	cout << ss << endl;
	return ss;
}

void f4()
{
	cout << f4_() << endl;
	/*
	string_view sv;
	{
		string s = "abcdefg";
		sv = s;
		//sv = "abcdefg";
		cout << sv << endl;
	//	string cc = "sgfdgsgs";
	}
	cout << sv << endl;
	*/
}


void f5()
{
	string s = "abcdefg";
	string_view sv = s;
	sv.remove_prefix(3);
	
	cout << sv << endl;
	cout << s << endl;
}

// flyweight
struct person
{
	int id_;
	std::string city_;
};

int f8()
{
	std::vector<person> persons;
	for (int i = 0; i < 100000; ++i)
		persons.push_back({ i, "Berlin" });
}

struct person2
{
	int id_;
	flyweight<std::string> city_;
	person2(int id, std::string city) : id_{ id }, city_{ std::move(city) } {}
};

int f9()
{
	std::vector<person2> persons;
	for (int i = 0; i < 100000; ++i)
		persons.push_back({ i, "Berlin" });
}
/*
void f6()
{
	flyweight<string> first_name1 = "abcd";
	flyweight<string> last_name1 = "dcba";

	flyweight<string> first_name2 = "abcd";
	flyweight<string> last_name2 = "pppqr";

	assert(&first_name1.get() == &first_name2.last_name.get());
}
*/

void f6()
{
	std::string_view str{ "balloon" };

	// Удаляем символ "b"
	str.remove_prefix(1);

	// Удаляем часть "oon"
	str.remove_suffix(3);

	// Помните, что предыдущие 2 команды не изменяют исходную строку, они работают лишь с её представлением
	std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
	std::cout << "str.data() is " << str.data() << '\n';
	std::cout << "str is " << str << '\n';
}
/*
Следите за тем, чтобы исходная строка, на которую ссылается объект std::string_view, не выходила за пределы области видимости и не изменялась до тех пор, 
пока используется ссылающийся на нее объект std::string_view.
*/
int main()
{
//	f1();
//	f2();
//	f3();
//	f4();
//	f5();
	return 0;
}