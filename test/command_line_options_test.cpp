#include<iostream>
#include "../lib/command_line_options.hpp"

using namespace std;

int main(int argc, char* argv[]) {
	command_line_options clo(argc, argv);

	cout << clo << endl;

	return 0;
}
