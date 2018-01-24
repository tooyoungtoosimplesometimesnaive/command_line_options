#ifndef COMMAND_LINE_OPTIONS_HPP
#define COMMAND_LINE_OPTIONS_HPP

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>

using std::ostream;
using std::vector;
using std::string;
using std::unordered_map;

class command_line_options {
	friend ostream& operator<<(ostream & os, const command_line_options& clo);

public:
	void emplace_map(string key, string value);

	command_line_options(int argc, char * argv[]);

private:
	unordered_map<string, vector<string>> map;

	vector<string> vargs;

	void get_options();
};

#endif

