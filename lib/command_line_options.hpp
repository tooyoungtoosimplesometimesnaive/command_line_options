#ifndef COMMAND_LINE_OPTIONS_HPP
#define COMMAND_LINE_OPTIONS_HPP

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>

using std::ostream;
using std::vector;
using std::string;
using std::unordered_map;
using std::find;

class command_line_options {
public:
	void emplace_map(unordered_map<string, vector<string>> & map, string key, string value) {
			auto got = map.find(key);
			if (got == map.end()) {
				vector<string> v = {value};
				map.emplace(key, v);
			}
			else {
				auto &vk = map[key];
				if (find(vk.begin(), vk.end(), value) != vk.end()) {
					vk.push_back(value);
				}
			}
	}

	auto get_options() {
		unordered_map<string, vector<string>> map;
		decltype(vargs.size()) i = 0;
		while (i < vargs.size()) {
			string arg = vargs[i];

			if (arg[0] == '-') {
				if (i + 1 < vargs.size()) {
					if (vargs[i + 1][0] != '-') {
						emplace_map(map, arg.substr(1), vargs[i + 1]);
						i++;
					}
					else {
						emplace_map(map, arg.substr(1), "true");
					}
				}
				else {
					emplace_map(map, arg.substr(1), "true");
				}
			}
			else {
				emplace_map(map, "_", arg);
			}
			i++;
		}
		return map;
	}

	command_line_options(int argc, char * argv[]) {
		int i = 0;
		while (i < argc) {
			string sarg {argv[i]};
			vargs.push_back(sarg);
			i ++;
		}
		map = get_options();
	}

	unordered_map<string, vector<string>> map;

	vector<string> vargs;

	friend ostream& operator<<(ostream & os, const command_line_options& clo);
};

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


#endif

