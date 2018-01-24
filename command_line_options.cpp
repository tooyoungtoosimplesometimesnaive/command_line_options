#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>

#include "command_line_options.hpp"

using std::ostream;
using std::vector;
using std::string;
using std::unordered_map;
using std::find;
using std::make_pair;

void command_line_options::emplace_map(string key, string value) {
	auto got = map.find(key);
	if (got == map.end()) {
		vector<string> v = {value};
		map.insert(make_pair(key, v));
	}
	else {
		auto &vk = map[key];
		if (find(vk.begin(), vk.end(), value) == vk.end()) {
			vk.push_back(value);
		}
	}
}

void command_line_options::get_options() {
	decltype(vargs.size()) i = 0;
	while (i < vargs.size()) {
		string arg = vargs[i];

		std::cout << arg << std::endl;

		if (arg[0] == '-') {
			if (i + 1 < vargs.size()) {
				if (vargs[i + 1][0] != '-') {
					emplace_map(arg.substr(1), vargs[i + 1]);
					i++;
				}
				else {
					emplace_map(arg.substr(1), "true");
				}
			}
			else {
				emplace_map(arg.substr(1), "true");
			}
		}
		else {
			emplace_map("_", arg);
		}
		i++;
	}
}

command_line_options::command_line_options(int argc, char * argv[]) {
	int i = 0;
	while (i < argc) {
		string sarg {argv[i]};
		vargs.push_back(sarg);
		i ++;
	}
	get_options();
}

ostream& operator<<(ostream & os, const command_line_options& clo) {
	for (auto it = clo.map.begin(); it != clo.map.end(); it++) {
		os << it->first << ": ";
		for (auto s : it->second) {
			os << s << " ";
		}
		os << std::endl;
	}
	return os;
};