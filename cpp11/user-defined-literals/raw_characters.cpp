#include <iostream>

using namespace std;

// Raw string literal. Used to avoid escaping of any character. 
// Anything between the delimiters becomes part of the string.
int main() {
	const char* str1 = "c:\\user\\test";
	const char* str2 = R"(c:\user\test)";

	const char* str3 = R"(hello
world\n
!!!)";

	cout << str1 << endl
		 << str2 << endl
		 << str3 << endl;

	return 0;
}

