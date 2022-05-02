#include <iostream>
#include <vector>

using namespace std;

union u1
{
	std::int32_t n;     // occupies 4 bytes
	std::uint16_t s[2]; // occupies 4 bytes
	std::uint8_t c;     // occupies 1 byte
}u;                     // the whole union occupies 4 bytes

// if u1 were a struct |n_1|n_2|n_3|n_4|s[0]_1|s[1]_2|c|
// now |n_1|n_2|n_3|n_4|s[0]_1|s[1]_2|c|

void first_example()
{
	/*
	u.c = 'b';

	cout << u.c << endl;
	cout << u.a << endl;
	*/
	// why the following is bad ?

	u.n = INT32_MAX;

	cout << u.n << endl;
	// UNDEFINED BEHAVIOR
	cout << u.s[0] << endl;
	cout << u.s[1] << endl;
	cout << u.c << endl;

	u.s[1] = 78;

	cout << u.s[1] << endl;
	// UNDEFINED BEHAVIOR
	cout << u.n << endl;
	cout << u.s[0] << endl;
	cout << u.c << endl;
}

// second example


enum class identifier_type { str, num };

/*
struct dict_entry {
	const char* name;

	identifier_type t;
	const char* s; // use s if t == str
	int i; // use i if t == num
};
*/

union identifier
{
	const char* s; // use s if t == str
	int i; // use i if t == num
}id;
struct dict_entry {
	const char* name;

	identifier_type t;
	identifier id;
};

void f(dict_entry* p)
{
	if (p->t == identifier_type::str)
		//cout << p->s;
		cout << p->id.s;
	else
		//cout << p->i;
		cout << p->id.i;
	// ...
}

void second_example()
{
	//dict_entry d1{ "David", identifier_type::num, "abcd", 7 };
	id.i = 7;
	dict_entry d1{ "David", identifier_type::num, id };

	cout << sizeof(d1) << endl;
	//f(&d1);
}

int main()
{
	//first_example();
	second_example();

	return 0;
}